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
    int                 _pitch;             // Pitch value
    int                 _velocity;          // Velocity values
    bool                _on;                // Whether the key is still being pressed
    static bool         _pedal;             // Whether the pedal is being pressed
    
public:
    MidiNoteConcrete(int pitch, int velocity);
    
    virtual bool        isOn() const override;
    virtual int         getPitch() const override;
    virtual int         getVelocity() const override;
    virtual bool        toDelete() const override;
    virtual void        setOff() override;
    virtual void        newPress(int velocity) override;
    virtual void        update() override;
    virtual void        draw() override;
};
