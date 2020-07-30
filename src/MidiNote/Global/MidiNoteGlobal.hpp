//
//  MidiNoteGlobal.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

class MidiNoteGlobal {
protected:
    int                 _window_width;
    int                 _window_height;
    
public:
    MidiNoteGlobal(int width, int height);
    virtual             ~MidiNoteGlobal() = default;
    
    virtual void        midiNoteOn() = 0;
    virtual void        midiNoteOff() = 0;
    virtual void        midiControlChange() = 0;
    virtual void        update() = 0;
    virtual void        draw() = 0;
    virtual bool        toDelete() const = 0;
    virtual void        windowResized(int width, int height) = 0;

};
