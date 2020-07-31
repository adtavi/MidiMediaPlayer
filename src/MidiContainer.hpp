//
//  MidiNotes.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include <list>
#include <memory>

#include "ofxMidiMessage.h"
#include "MidiGlobal/Light.hpp"
#include "Particles.hpp"
#include "MidiNote.hpp"
#include "DecoratorModel.hpp"
#include "DecoratorLight.hpp"
#include "DecoratorSphere.hpp"

class MidiContainer {
    list<unique_ptr<MidiNote::Base>>        _midi_notes;
    list<unique_ptr<MidiGlobal::Base>>      _midi_note_global;
    int                                     _window_width;
    int                                     _window_height;
    
public:
    MidiContainer(int window_width, int window_height);
    
    void    processMidiNoteOn(const ofxMidiMessage & message);
    void    processMidiNoteOff(const ofxMidiMessage & message);
    void    processMidiControlChange(const ofxMidiMessage & message);
    void    update();
    void    draw();
    void    windowResized(int width, int height);
};
