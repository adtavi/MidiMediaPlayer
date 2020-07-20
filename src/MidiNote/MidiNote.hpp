//
//  MidiNote.hpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

#include <stdio.h>
#include "ofGraphics.h"

// 21- 108
class MidiNote {
   
protected:
    static bool         _pedal; // Whether the pedal is being pressed

public:
    MidiNote() = default;
    virtual             ~MidiNote() = default;
        
    static void         setPedal(bool pedal);
    static bool         isPedal();
    
    virtual int         getPitch() const = 0;
    virtual int         getVelocity() const = 0;
    virtual bool        isOn() const = 0;
    virtual bool        toDelete() const = 0;
    virtual void        setOff() = 0;
    virtual void        newPress(int velocity) = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
};
