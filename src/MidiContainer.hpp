//
//  MidiContainer.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include <list>
#include <memory>

#include "ofxMidiMessage.h"
#include "MidiSettings.hpp"
#include "MidiGlobalLight.hpp"
#include "MidiGlobalParticles.hpp"
#include "MidiGlobalFloor.hpp"
#include "MidiNote.hpp"
#include "MidiNoteDecoratorModel.hpp"
#include "MidiNoteDecoratorLight.hpp"
#include "MidiNoteDecoratorSphere.hpp"

class MidiContainer {
    friend class TestMidiContainer;

    list<unique_ptr<MidiNoteBase>>      _midi_notes;
    list<unique_ptr<MidiGlobalBase>>    _midi_note_global;
    
    void    process_midi_note_on(const ofxMidiMessage & message);
    void    process_midi_note_off(const ofxMidiMessage & message);
    void    process_midi_control_change(const ofxMidiMessage & message);
    
public:
    MidiContainer(int window_width, int window_height);
    
    void    process_midi_message(ofxMidiMessage & message);
    void    update();
    void    draw();
    void    window_resized(int width, int height);
};
