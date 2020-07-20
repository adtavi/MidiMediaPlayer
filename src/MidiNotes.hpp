//
//  MidiNotes.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include <list>
#include "ofxMidiMessage.h"
#include "ofMain.h"
#include "MidiNoteConcrete.hpp"
#include "MidiNoteSphere.hpp"
#include "MidiNoteLight.hpp"

class MidiNotes: public std::list<unique_ptr<MidiNote>> {
    
public:
    void    processMidiNoteOn(const ofxMidiMessage & message);
    void    processMidiNoteOff(const ofxMidiMessage & message);
    void    processMidiControlChange(const ofxMidiMessage & message);
    void    update();
};
