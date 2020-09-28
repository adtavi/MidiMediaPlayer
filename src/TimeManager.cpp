//
//  TimeContainer.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "TimeManager.hpp"

TimeManager::TimeManager() {
    _first_note = true;
    _delta_note = 0;
    _delta_note_acc = 0;
    _num_missmatched_notes = 0;
    _half_note = 0;
    
    _first_pedal = true;
    _delta_pedal = 0;
    _delta_pedal_acc = 0;
    _num_missmatched_pedals = 0;
    
    _elapsed_time = 0;
    _time_since_update = 0;
}

void TimeManager::process_midi_message(const ofxMidiMessage & message) {
    // Scrap first midi note on
    if (_first_note && message.status == MIDI_NOTE_ON) {
        _first_note = false;
        return;
    }
    // Scrap first midi pedal on
    else if (_first_pedal && message.status == MIDI_CONTROL_CHANGE && message.control == 64 && message.value == 127) {
        _first_pedal = false;
        return;
    }
    
    // Accumulate deltas
    if (!_first_note) {
        _delta_note_acc += message.deltatime;
    }
    
    // Accumulate deltas
    if (!_first_pedal) {
        _delta_pedal_acc += message.deltatime;
    }
    
    if (message.status == MIDI_NOTE_ON && _delta_note_acc > _delta_note_min) {
        process_delta_note(_delta_note_acc);
        _delta_note_acc = 0;
    } else if (message.status == MIDI_CONTROL_CHANGE && message.control == 64 && message.value == 127) {
        process_delta_pedal(_delta_pedal_acc);
        _delta_pedal_acc = 0;
    }
}

uint64_t    TimeManager::get_delta_note() const {
    return _delta_note;
}

uint64_t    TimeManager::get_delta_pedal() const {
    return _delta_pedal;
}

void        TimeManager::update_elapsed_time(uint64_t elapsed_time) {
    _time_since_update = (elapsed_time - _elapsed_time);
    _elapsed_time = elapsed_time;
}

uint64_t    TimeManager::get_time_since_update() const {
    return _time_since_update;
}

void        TimeManager::process_delta_note(double delta) {
    if (_delta_notes.empty() || (delta > _delta_note * _delta_lower_threshold && delta < _delta_note * _delta_upper_threshold)) {
        
        add_delta_note(delta);
        
        // Checking if we're playing eigth notes by cheking the pedal
        double notes_per_pedal = _delta_pedal / _delta_note;
        if (_delta_notes.size() > 8 && notes_per_pedal > 8 * _delta_lower_threshold && notes_per_pedal < 8 * _delta_upper_threshold) {
            to_double_duration_notes();
        }
    } else if (delta * 2 > _delta_note *_delta_lower_threshold && delta * 2 < _delta_note * _delta_upper_threshold) {
        if (_half_note == 0) {
            _half_note = delta;
        } else {
            add_delta_note(_half_note + delta);
            _half_note = 0;
        }
    }
    else {
        _num_missmatched_notes++;
    }
    
    // After 10 missmatched notes, reset
    if (_num_missmatched_notes > 10) {
        _delta_notes.clear();
        _num_missmatched_notes = 0;
        _delta_note = 0;
    }
}

void    TimeManager::add_delta_note(double delta) {
    _delta_notes.push_back(delta);
    
    // calculate new mean
    _delta_note = accumulate( _delta_notes.begin(), _delta_notes.end(), 0.0) / _delta_notes.size();
    _num_missmatched_notes = 0;
}

void    TimeManager::to_double_duration_notes() {
    vector<double> double_notes;
    
    for (int i = 0; i < _delta_notes.size() - 1; i=i+2) {
        double_notes.push_back(_delta_notes[i] + _delta_notes[i+1]);
    }
    
    _delta_notes = double_notes;
    _delta_note = accumulate( _delta_notes.begin(), _delta_notes.end(), 0.0) / _delta_notes.size();
}

void        TimeManager::process_delta_pedal(double delta) {
    if (_delta_pedals.empty() || (delta > _delta_pedal * _delta_lower_threshold && delta < _delta_pedal * _delta_upper_threshold)) {
        _delta_pedals.push_back(delta);
       
        // calculate new mean
        _delta_pedal = accumulate( _delta_pedals.begin(), _delta_pedals.end(), 0.0) / _delta_pedals.size();
        _num_missmatched_pedals = 0;
    } else {
        _num_missmatched_pedals++;
    }
    
    // After 10 missmatched pedals, reset
    if (_num_missmatched_pedals > 2) {
        _delta_pedals.clear();
        _num_missmatched_pedals = 0;
        _delta_pedal = 0;
    }
}
