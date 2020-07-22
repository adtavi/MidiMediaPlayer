//
//  MidiNoteDecorator.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "MidiNote.hpp"

class MidiNoteDecorator: public MidiNote {
    
protected:
    MidiNote *          _midi_note;
    
public:
    MidiNoteDecorator(MidiNote * midi_note);
    ~MidiNoteDecorator();
    
    static void         setFrame(int width, int height);
    virtual bool        isOn() const override;
    virtual int         getPitch() const override;
    virtual int         getVelocity() const override;
};
