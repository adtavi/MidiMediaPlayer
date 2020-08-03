//
//  MidiSettings.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 31/07/2020.
//

#pragma once

#include <string>

using namespace std;

class MidiSettings
{
private:
    MidiSettings() = default;
    
    // Midi keyboard
    static constexpr int    _num_keys = 87;     // Number of keys on the keyboard
    static constexpr int    _min_pitch = 21;    // Pitch value of first key [21- 108]
    static constexpr int    _num_vel = 100;      // Keyboard has 99 degrees of velocity

    static bool             _pedal;             // Whether the pedal is being pressed
    
    // Window size
    static int              _window_width;      // Window width
    static int              _window_height;     // Window height
    static int              _window_depth;      // Window depth
    static float            _velocity_height;   // Amount of height for each velocity value
    static float            _key_width;         // Window width for each key
    
    static std::string      _data_path;         // Path were the model and textures are
    
public:
    // Midi keyboard
    static int              get_num_keys();
    static int              get_min_pitch();
    static int              get_num_vel();
    
    // Pedal
    static void             set_pedal(bool pedal);
    static bool             is_pedal();
    
    // Window
    static void             set_window(int width, int height);
    static int              get_window_width();
    static int              get_window_height();
    static int              get_window_depth();
    static float            get_velocity_height();
    static float            get_key_width();
    static float            calc_y_by_velocity(int velocity);
    static float            calc_x_by_pitch(int pitch);
    
    // Data path
    static void             set_data_path(const char * data_path);
    static const string&    get_data_path();
};
