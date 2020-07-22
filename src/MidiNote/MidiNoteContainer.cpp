//
//  MidiNotes.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteContainer.hpp"

MidiNoteContainer::MidiNoteContainer() {
    _midi_note_global.push_back(std::move(std::make_unique<MidiNoteGlobalParticles>()));
    _midi_note_global.push_back(std::move(std::make_unique<MidiNoteGlobalLight>()));
}

void MidiNoteContainer::processMidiNoteOn(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = std::find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const std::unique_ptr<MidiNote> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {   // If the note is on the container
        (*it).get()->newPress(message.velocity);           // Key pressed again
    } else {
        // Decorating note
        MidiNoteConcrete * midi_note_concrete = new MidiNoteConcrete(message.pitch, message.velocity);
        MidiNoteSphere * midi_note_sphere = new MidiNoteSphere(midi_note_concrete);
        MidiNoteLight * midi_note_light = new MidiNoteLight(midi_note_sphere);
        _midi_notes.push_back(std::move(std::make_unique<MidiNoteModel>(midi_note_light)));
    }
    
    std::for_each(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::midiNoteOn));
}

void MidiNoteContainer::processMidiNoteOff(const ofxMidiMessage & message) {
    // Find the note with the same pitch
    auto it = std::find_if(_midi_notes.begin(), _midi_notes.end(), [&message](const std::unique_ptr<MidiNote> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != _midi_notes.end()) {  // If the note is on the container
        (*it).get()->setOff();
    } else {
        // Error: a note went off and it wasn't added to the container (!)
        std::cout << "NOTE OFF not registered" << message.pitch << std::endl;
    }
    
    std::for_each(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::midiNoteOff));
}

void MidiNoteContainer::processMidiControlChange(const ofxMidiMessage & message) {
    if (message.control == 64) {
        MidiNote::setPedal(message.value == 127);
    }
    
    std::for_each(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::midiControlChange));
}

void MidiNoteContainer::update() {
    std::for_each(_midi_notes.begin(), _midi_notes.end(), std::mem_fn(&MidiNote::update));
    
    // Erase notes if needed
    _midi_notes.erase(std::remove_if(_midi_notes.begin(), _midi_notes.end(), std::mem_fn(&MidiNote::toDelete)), _midi_notes.end());
    
    std::for_each(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::update));
    _midi_note_global.erase(std::remove_if(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::toDelete)), _midi_note_global.end());
}

void MidiNoteContainer::draw() {
    std::for_each(_midi_notes.begin(), _midi_notes.end(), std::mem_fn(&MidiNote::draw));
    std::for_each(_midi_note_global.begin(), _midi_note_global.end(), std::mem_fn(&MidiNoteGlobal::draw));
}
