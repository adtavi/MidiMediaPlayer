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
#include "MidiNoteSphere.hpp"
#include "MidiNoteConcrete.hpp"

class MidiNotes: public std::list<unique_ptr<MidiNote>> {
    
public:
    void    processMidiNoteOn(const ofxMidiMessage & message, const ofColor & color);
    void    processMidiNoteOff(const ofxMidiMessage & message);
    void    processMidiControlChange(const ofxMidiMessage & message);
    void    update();
};
