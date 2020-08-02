//
//  MidiGlobalBase.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include <iostream>
#include "MidiSettings.hpp"

using namespace std;

class MidiGlobalBase {
public:
    virtual             ~MidiGlobalBase() = default;
    
    virtual void        midi_note_on() = 0;
    virtual void        midi_note_off() = 0;
    virtual void        midi_control_change() = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
    virtual bool        to_delete() const = 0;
    virtual void        window_resized() = 0;
};
