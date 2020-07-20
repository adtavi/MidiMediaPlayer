//
//  MidiNote.hpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

#include <stdio.h>
#include "MidiNote.hpp"

class MidiNoteConcrete: public MidiNote {
    
private:
    
public:
    MidiNoteConcrete(int pitch, int velocity);
    
    virtual bool        isOn() const override;
    virtual int         getPitch() const override;
    virtual int         getVelocity() const override;
    virtual ofColor     getColor() const override;
    virtual bool        toDelete() const override;
    virtual bool        toDraw() const override;
    virtual void        setOff() override;
    virtual void        newPress(int velocity) override;
    virtual void        update() override;
    virtual void        draw() override;
};
