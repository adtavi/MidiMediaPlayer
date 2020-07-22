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
#include "MidiNoteConcrete.hpp"
#include "MidiNoteLight.hpp"
#include "MidiNoteModel.hpp"
#include "MidiNoteGlobalParticles.hpp"
#include "MidiNoteGlobalLight.hpp"
#include "MidiNoteSphere.hpp"

class MidiNoteContainer {
    std::list<std::unique_ptr<MidiNote>>         _midi_notes;
    std::list<std::unique_ptr<MidiNoteGlobal>>   _midi_note_global;
    
public:
    MidiNoteContainer();
    
    void    processMidiNoteOn(const ofxMidiMessage & message);
    void    processMidiNoteOff(const ofxMidiMessage & message);
    void    processMidiControlChange(const ofxMidiMessage & message);
    void    update();
    void    draw();
};
