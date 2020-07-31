//
//  MidiNotes.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiContainer.hpp"

MidiContainer::MidiContainer(int window_width, int window_height) {
    MidiSettings::setWindow(window_width, window_height);
    _midi_note_global.push_back(move(make_unique<MidiGlobal::Particles>()));
    _midi_note_global.push_back(move(make_unique<MidiGlobal::Light>()));
}

void MidiContainer::processMidiNoteOn(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const unique_ptr<MidiNote::Base> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {   // If the note is on the container
        (*it).get()->newPress(message.velocity);           // Key pressed again
    } else {
        // Decorating note
        MidiNote::MidiNote * midi_note_concrete = new MidiNote::MidiNote(message.pitch, message.velocity);
        MidiNote::DecoratorSphere * midi_note_sphere = new MidiNote::DecoratorSphere(midi_note_concrete);
        MidiNote::DecoratorLight * midi_note_light = new MidiNote::DecoratorLight(midi_note_sphere);
        _midi_notes.push_back(std::move(std::make_unique<MidiNote::DecoratorModel>(midi_note_light)));
    }
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::midiNoteOn));
}

void MidiContainer::processMidiNoteOff(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const unique_ptr<MidiNote::Base> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {  // If the note is on the container
        (*it).get()->setOff();
    } else {
        // Error: a note went off and it wasn't added to the container (!)
        cout << "NOTE OFF not registered" << message.pitch << endl;
    }
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::midiNoteOff));
}

void MidiContainer::processMidiControlChange(const ofxMidiMessage & message) {
    if (message.control == 64) {
        MidiSettings::setPedal(message.value == 127);
    }
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::midiControlChange));
}

void MidiContainer::update() {
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNote::Base::update));
    
    // Erase notes if needed
    _midi_notes.erase(remove_if(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNote::Base::toDelete)), _midi_notes.end());
    
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::update));
    _midi_note_global.erase(remove_if(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::toDelete)), _midi_note_global.end());
}

void MidiContainer::draw() {
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNote::Base::draw));
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::draw));
}

void MidiContainer::windowResized(int window_width, int window_height) {
    MidiSettings::setWindow(window_width, window_height);
    for_each(_midi_notes.begin(), _midi_notes.end(), mem_fn(&MidiNote::Base::windowResized));
    for_each(_midi_note_global.begin(), _midi_note_global.end(), mem_fn(&MidiGlobal::Base::windowResized));
}
