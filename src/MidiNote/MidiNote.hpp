//
//  MidiNote.hpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

#include "Base.hpp"

namespace MidiNote {

class MidiNote: public Base {
    
private:
    int                 _pitch;             // Pitch value
    int                 _velocity;          // Velocity values
    bool                _on;                // Whether the key is still being pressed
    
public:
    MidiNote(int pitch, int velocity);
    
    virtual bool        isOn() const override;
    virtual int         getPitch() const override;
    virtual int         getVelocity() const override;
    virtual bool        toDelete() const override;
    virtual void        setOff() override;
    virtual void        newPress(int velocity) override;
    virtual void        update() override;
    virtual void        draw() override;
    virtual void        windowResized() override;
};

}
