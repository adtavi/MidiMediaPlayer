//
//  MidiNoteDecoratorLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#pragma once

#include "MidiNoteDecoratorLightBase.hpp"

class MidiNoteDecoratorLight: public MidiNoteDecoratorLightBase {
    friend class    TestMidiNoteDecoratorLight;
        
public:
    MidiNoteDecoratorLight(MidiNoteBase* midi_note);
    
    virtual void    look_at() override;
    virtual void    set_position() override;
};

