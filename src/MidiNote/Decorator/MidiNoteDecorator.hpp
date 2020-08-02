//
//  MidiNoteDecorator.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "MidiNoteBase.hpp"

class MidiNoteDecorator: public MidiNoteBase {
    
protected:
    MidiNoteBase*          _midi_note;
    
    MidiNoteDecorator(MidiNoteBase* midi_note);
    
public:
    ~MidiNoteDecorator();

    virtual bool    is_on() const override;
    virtual int     get_pitch() const override;
    virtual int     get_velocity() const override;
};
