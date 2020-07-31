//
//  MidiNoteGlobal.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include <iostream>
#include "MidiSettings.hpp"

using namespace std;

namespace MidiGlobal {

class Base {
public:
    virtual             ~Base() = default;
    
    virtual void        midiNoteOn() = 0;
    virtual void        midiNoteOff() = 0;
    virtual void        midiControlChange() = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
    virtual bool        toDelete() const = 0;
    virtual void        windowResized() = 0;
};

}
