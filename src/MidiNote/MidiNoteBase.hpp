//
//  MidiNoteBase.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

#include <iostream>
#include "MidiSettings.hpp"

using namespace std;

class MidiNoteBase {
    
public:
    MidiNoteBase() = default;
    virtual             ~MidiNoteBase() = default;
    
    virtual int         get_pitch() const = 0;
    virtual int         get_velocity() const = 0;
    virtual bool        is_on() const = 0;
    virtual bool        to_delete() const = 0;
    virtual void        set_off() = 0;
    virtual void        new_press(int velocity) = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
    virtual void        window_resized() = 0;
};
