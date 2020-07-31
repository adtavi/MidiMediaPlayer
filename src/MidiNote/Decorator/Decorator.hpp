//
//  MidiNoteDecorator.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "MidiNote/Base.hpp"

namespace MidiNote {

class Decorator: public Base {
    
protected:
    Base*          _midi_note;
    
public:
    Decorator(Base* midi_note);
    ~Decorator();

    virtual bool    isOn() const override;
    virtual int     getPitch() const override;
    virtual int     getVelocity() const override;
};

}
