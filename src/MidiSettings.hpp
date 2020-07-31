//
//  MidiSettings.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 31/07/2020.
//

#pragma once

class MidiSettings
{
private:
    MidiSettings() = default;
    
    // Midi keyboard
    static constexpr int    _num_keys = 87;     // Number of keys on the keyboard
    static constexpr int    _min_pitch = 21;    // Pitch value of first key [21- 108]
    static constexpr int    _num_vel = 99;      // Keyboard has 99 degrees of velocity

    static bool             _pedal;             // Whether the pedal is being pressed
    
    // Window size
    static int              _window_width;      // Window width
    static int              _window_height;     // Window height
    static float            _velocity_height;   // Amount of height for each velocity value
    static float            _key_width;         // Window width for each key
    
public:
    // Midi keyboard
    static int              getNumKeys();
    static int              getMinPitch();
    static int              getNumVel();
    
    // Pedal
    static void             setPedal(bool pedal);
    static bool             isPedal();
    
    // Window
    static void             setWindow(int width, int height);
    static int              getWindowWidth();
    static int              getWindowHeight();
    static float            getVelocityHeight();
    static float            getKeyWidth();
    static float            calcYByVelocity(int velocity);
};
