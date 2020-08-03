//
//  MidiContainer.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiContainer.hpp"

MidiContainer::MidiContainer(int window_width, int window_height) {
    MidiSettings::set_window(window_width, window_height);
    _midi_note_global.push_back(move(make_unique<MidiGlobalParticles>()));
    _midi_note_global.push_back(move(make_unique<MidiGlobalLight>()));
    _midi_note_global.push_back(move(make_unique<MidiGlobalFloor>()));
}

void MidiContainer::process_midi_message(ofxMidiMessage & message) {
    if (message.status == MIDI_NOTE_ON) {
        process_midi_note_on(message);
    } else if (message.status == MIDI_NOTE_OFF) {
        process_midi_note_off(message);
    } else if (MIDI_CONTROL_CHANGE) {
        process_midi_control_change(message);
    }
    else {
        cout << message.toString() << endl;
    }
}

void MidiContainer::process_midi_note_on(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const unique_ptr<MidiNote::MidiNoteBase> & midi_note){
        return midi_note.get()->get_pitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {   // If the note is on the container
        (*it).get()->new_press(message.velocity);           // Key pressed again
    } else {
        // Decorating note
        MidiNote * midi_note_concrete = new MidiNote(message.pitch, message.velocity);
        MidiNoteDecoratorSphere * midi_note_sphere = new MidiNoteDecoratorSphere(midi_note_concrete);
        MidiNoteDecoratorLight * midi_note_light = new MidiNoteDecoratorLight(midi_note_sphere, midi_note_sphere);
        _midi_notes.push_back(move(make_unique<MidiNoteDecoratorModel>(midi_note_light, midi_note_sphere)));
    }
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::midi_note_on));
}

void MidiContainer::process_midi_note_off(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const unique_ptr<MidiNote::MidiNoteBase> & midi_note){
        return midi_note.get()->get_pitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {  // If the note is on the container
        (*it).get()->set_off();
    }
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::midi_note_off));
}

void MidiContainer::process_midi_control_change(const ofxMidiMessage & message) {
    if (message.control == 64) {
        if (message.value == 127) {
            MidiSettings::set_pedal(true);
        } else if (message.value == 0) {
            MidiSettings::set_pedal(false);
        }
    
        for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::midi_control_change));
    }
}

void MidiContainer::update() {
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNoteBase::update));
    
    // Erase notes if needed
    _midi_notes.erase(remove_if(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNoteBase::to_delete)), _midi_notes.end());
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::update));
    _midi_note_global.erase(remove_if(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::to_delete)), _midi_note_global.end());
}

void MidiContainer::draw() {
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNoteBase::draw));
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::draw));
}

void MidiContainer::window_resized(int window_width, int window_height) {
    MidiSettings::set_window(window_width, window_height);
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNoteBase::window_resized));
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobalBase::window_resized));
}
