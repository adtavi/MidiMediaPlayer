//
//  TestMidiSettings.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "catch.hpp"
#include "TimeManager.hpp"

#include <iostream>

using namespace std;

class TestTimeManager
{
    unique_ptr<TimeManager> _time_manager;
    
public:
    TestTimeManager() {
        _time_manager = make_unique<TimeManager>();
    };
    
    void process_delta_note(double delta) {
        _time_manager.get()->process_delta_note(delta);
    }

    void add_delta_note(double delta) {
        _time_manager.get()->add_delta_note(delta);
    }
    
    void eigth_to_quarter_notes() {
        _time_manager.get()->to_double_duration_notes();
    }
    
    void process_delta_pedal(double delta) {
        _time_manager.get()->process_delta_pedal(delta);
    }
    
    void process_midi_message(const ofxMidiMessage & message) {
        _time_manager.get()->process_midi_message(message);
    }
    
    void update_elapsed_time(uint64_t elapsed_time) {
        _time_manager.get()->update_elapsed_time(elapsed_time);
    }
    
    uint64_t get_delta_note() {
        return _time_manager.get()->get_delta_note();
    }
    
    uint64_t get_delta_note_acc() {
        return _time_manager.get()->_delta_note_acc;
    }
    
    uint64_t get_delta_pedal() {
        return _time_manager.get()->get_delta_pedal();
    }
    
    uint64_t get_delta_pedal_acc() {
        return _time_manager.get()->_delta_pedal_acc;
    }
    
    uint64_t get_time_since_update() {
        return _time_manager.get()->get_time_since_update();
    }
    
    bool get_first_note() {
        return _time_manager.get()->_first_note;
    }
    bool get_first_pedal() {
        return _time_manager.get()->_first_pedal;
    }
    
     unsigned short get_num_missmatched_notes() {
        return _time_manager.get()->_num_missmatched_notes;
    }
    
     unsigned short get_num_missmatched_pedals() {
        return _time_manager.get()->_num_missmatched_pedals;
    }
    
    double get_half_note() {
        return _time_manager.get()->_half_note;
    }
    
};

TEST_CASE_METHOD(TestTimeManager, "TimeManager", "[TimeManager]" ) {
    REQUIRE(get_first_note());
    REQUIRE(get_delta_note() == 0);
    REQUIRE(get_delta_note_acc() == 0);
    REQUIRE(get_num_missmatched_notes() == 0);
    REQUIRE(get_half_note() == 0);
    
    REQUIRE(get_first_pedal());
    REQUIRE(get_delta_pedal() == 0);
    REQUIRE(get_delta_pedal_acc() == 0);
    REQUIRE(get_num_missmatched_pedals() == 0);
    
    REQUIRE(get_time_since_update() == 0);
    REQUIRE(get_time_since_update() == 0);
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::process_midi_message_note", "[TimeManager]" ) {
    double deltatime = 6;
    ofxMidiMessage message;
    message.status = MIDI_NOTE_ON;
    message.deltatime = deltatime;
    REQUIRE(get_first_note());
    
    process_midi_message(message);
    REQUIRE(get_delta_note_acc() == 0);
    REQUIRE_FALSE(get_first_note());
    
    process_midi_message(message);
    REQUIRE(get_delta_note_acc() == deltatime);
    message.deltatime = 80;
    
    process_midi_message(message);
    REQUIRE(get_delta_note_acc() == 0);
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::process_midi_message_pedal", "[TimeManager]" ) {
    double deltatime = 6;
    ofxMidiMessage message_pedal;
    message_pedal.status = MIDI_CONTROL_CHANGE;
    message_pedal.control = 64;
    message_pedal.value = 127;
    REQUIRE(get_first_pedal());
    
    process_midi_message(message_pedal);
    REQUIRE(get_delta_pedal_acc() == 0);
    REQUIRE_FALSE(get_first_pedal());
    
    process_midi_message(message_pedal);
    REQUIRE(get_delta_pedal_acc() == deltatime);
    message_pedal.deltatime = 80;
    
    process_midi_message(message_pedal);
    REQUIRE(get_delta_pedal_acc() == 0);
}


TEST_CASE_METHOD(TestTimeManager, "TimeManager::process_midi_message", "[TimeManager]" ) {
    double deltatime = 6;
    ofxMidiMessage message_note;
    message_note.status = MIDI_NOTE_ON;
    message_note.deltatime = deltatime;
    REQUIRE(get_first_note());
    REQUIRE(get_first_pedal());

    process_midi_message(message_note);
    REQUIRE(get_delta_note_acc() == 0);
    REQUIRE_FALSE(get_first_note());
    
    ofxMidiMessage message_pedal;
    message_pedal.status = MIDI_CONTROL_CHANGE;
    message_pedal.control = 64;
    message_pedal.value = 127;
    message_pedal.deltatime = deltatime;
    process_midi_message(message_pedal);
    REQUIRE(get_delta_pedal_acc() == 0);
    REQUIRE_FALSE(get_first_pedal());
    
    process_midi_message(message_note);
    REQUIRE(get_delta_note_acc() == deltatime);
    REQUIRE(get_delta_pedal_acc() == deltatime);
    
    process_midi_message(message_pedal);
    REQUIRE(get_delta_note_acc() == deltatime*2);
    REQUIRE(get_delta_pedal_acc() == deltatime*2);
    
    message_note.deltatime = 80;
    process_midi_message(message_note);
    REQUIRE(get_delta_note_acc() == 0);
    REQUIRE(get_delta_pedal_acc() == deltatime*2+80);
    
    message_pedal.deltatime = 80;
    process_midi_message(message_pedal);
    REQUIRE(get_delta_pedal_acc() == 0);
    REQUIRE(get_delta_note_acc() == 0);
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::update_elapsed_time", "[TimeManager]" ) {
//void        TimeContainer::update_elapsed_time(uint64_t elapsed_time) {
//    _time_since_update = (elapsed_time - _elapsed_time);
//    _elapsed_time = elapsed_time;
//}
}


TEST_CASE_METHOD(TestTimeManager, "TimeManager::process_delta_note", "[TimeManager]" ) {
//void        TimeContainer::process_delta_note(double delta) {
//    if (_delta_notes.empty() || (delta > _delta_note * _delta_lower_threshold && delta < _delta_note * _delta_upper_threshold)) {
//
//        add_delta_note(delta);
//
//        // Checking if we're playing eigth notes by cheking the pedal
//        double notes_per_pedal = _delta_pedal / _delta_note;
//        if (_delta_notes.size() > 8 && notes_per_pedal > 8 * _delta_lower_threshold && notes_per_pedal < 8 * _delta_upper_threshold) {
//            eigth_to_quarter_notes();
//        }
//    } else if (delta * 2 > _delta_note *_delta_lower_threshold && delta * 2 < _delta_note * _delta_upper_threshold) {
//        if (_quarter_note == 0) {
//            _quarter_note = delta;
//        } else {
//            add_delta_note(_quarter_note + delta);
//            _quarter_note = 0;
//        }
//    }
//    else {
//        _num_missmatched_notes++;
//    }
//
//    // After 10 missmatched notes, reset
//    if (_num_missmatched_notes > 10) {
//        _delta_notes.clear();
//        _num_missmatched_notes = 0;
//        _delta_note = 0;
//    }
//}
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::add_delta_note", "[TimeManager]" ) {
//void    TimeContainer::add_delta_note(double delta) {
//    _delta_notes.push_back(delta);
//
//    // calculate new mean
//    _delta_note = accumulate( _delta_notes.begin(), _delta_notes.end(), 0.0) / _delta_notes.size();
//    _num_missmatched_notes = 0;
//}
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::to_double_duration_notes", "[TimeManager]" ) {
//void    TimeContainer::to_double_duration_notes() {
//    vector<double> quarters;
//
//    for (int i = 0; i < _delta_notes.size() - 1; i=i+2) {
//        quarters.push_back(_delta_notes[i] + _delta_notes[i+1]);
//    }
//
//    _delta_notes = quarters;
//    _delta_note = accumulate( _delta_notes.begin(), _delta_notes.end(), 0.0) / _delta_notes.size();
//}
}

TEST_CASE_METHOD(TestTimeManager, "TimeManager::process_delta_pedal", "[TimeManager]" ) {
//void        TimeContainer::process_delta_pedal(double delta) {
//    if (_delta_pedals.empty() || (delta > _delta_pedal * _delta_lower_threshold && delta < _delta_pedal * _delta_upper_threshold)) {
//        _delta_pedals.push_back(delta);
//
//        // calculate new mean
//        _delta_pedal = accumulate( _delta_pedals.begin(), _delta_pedals.end(), 0.0) / _delta_pedals.size();
//        _num_missmatched_pedals = 0;
//    } else {
//        _num_missmatched_pedals++;
//    }
//
//    // After 10 missmatched pedals, reset
//    if (_num_missmatched_pedals > 2) {
//        _delta_pedals.clear();
//        _num_missmatched_pedals = 0;
//        _delta_pedal = 0;
//    }
//}
}
