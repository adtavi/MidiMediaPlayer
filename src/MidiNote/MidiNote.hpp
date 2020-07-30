//
//  MidiNote.hpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

class MidiNote {
    
protected:
    static bool             _pedal;             // Whether the pedal is being pressed
    static constexpr int    _num_keys = 87;     // Number of keys on the keyboard
    static constexpr int    _min_pitch = 21;    // Pitch value of first key [21- 108]
    static constexpr int    _num_vel = 127;     // Keyboard has 99 degrees of velocity
    
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
    virtual void        windowResized(int width, int height) = 0;
    virtual int         getWindowWidth() const = 0;
    virtual int         getWindowHeight() const = 0;
};
