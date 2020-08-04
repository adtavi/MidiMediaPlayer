//
//  MidiNoteDecoratorLightLookAtNode.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#pragma once

#include "MidiNoteDecoratorLightBase.hpp"
#include "ofNode.h"

class MidiNoteDecoratorLightLookAtNode: public MidiNoteDecoratorLightBase {
    friend class    TestMidiNoteDecoratorLightLookAtNode;

    ofNode*         _look_at_node;
    
public:
    MidiNoteDecoratorLightLookAtNode(MidiNoteBase* midi_note, ofNode * node);
        
    virtual void    look_at() override;
    virtual void    set_position() override;
};

