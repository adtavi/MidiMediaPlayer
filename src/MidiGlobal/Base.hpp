//
//  MidiNoteGlobal.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include <iostream>

using namespace std;

namespace MidiGlobal {

class Base {
protected:
    int                 _window_width;
    int                 _window_height;
    
public:
    Base(int width, int height);
    virtual             ~Base() = default;
    
    virtual void        midiNoteOn() = 0;
    virtual void        midiNoteOff() = 0;
    virtual void        midiControlChange() = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
    virtual bool        toDelete() const = 0;
    virtual void        windowResized(int width, int height) = 0;
};

}
