//
//  MidiNotes.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNotes.hpp"

void MidiNotes::processMidiNoteOn(const ofxMidiMessage & message) {
    auto it = std::find_if(begin(), end(), [&message](const std::unique_ptr<MidiNote> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != end()) {   // If the note's been played recently
        (*it).get()->newPress(message.velocity);           // Key pressed again
    } else {
        MidiNoteConcrete * midi_note_concrete = new MidiNoteConcrete(message.pitch, message.velocity);
        MidiNoteSphere * midi_note_sphere = new MidiNoteSphere(midi_note_concrete);
        push_back(std::move(std::make_unique<MidiNoteLight>(midi_note_sphere)));
    }
}

void MidiNotes::processMidiNoteOff(const ofxMidiMessage & message) {
    auto it = std::find_if(begin(), end(), [&message](const std::unique_ptr<MidiNote> & midi_note){
        return midi_note.get()->getPitch() == message.pitch;
    });
    
    if (it != end()) {
        (*it).get()->setOff();
    } else {
        std::cout << "Note off not registered" << message.pitch << std::endl;
    }
}

void MidiNotes::processMidiControlChange(const ofxMidiMessage & message) {
    if (message.control == 64) {
        MidiNote::setPedal(message.value == 127);
    }
}

void MidiNotes::update() {
    for (auto & midi_note: *this) {
        midi_note->update();             // Update position
    }
    
    // Erase notes if needed
    erase(std::remove_if(begin(), end(), [](const std::unique_ptr<MidiNote> & midi_note) {
        return midi_note.get()->toDelete();
    }), end());
}
