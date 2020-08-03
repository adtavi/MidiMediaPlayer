//
//  MidiSettings.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 31/07/2020.
//

#include "MidiSettings.hpp"

bool    MidiSettings::_pedal = false;
int     MidiSettings::_window_width = 0;
int     MidiSettings::_window_height = 0;
int     MidiSettings::_window_depth = 0;
float   MidiSettings::_velocity_height = 0;
float   MidiSettings::_key_width = 0;
string  MidiSettings::_data_path = "";

void    MidiSettings::set_window(int width, int height) {
    _window_width = width;
    _window_height = height;
    _window_depth = height;
    _velocity_height = static_cast<float>(height) / static_cast<float>(_num_vel);
    _key_width = static_cast<float>(width) / static_cast<float>(_num_keys);
}

int     MidiSettings::get_num_keys() {
    return _num_keys;
}

int     MidiSettings::get_min_pitch() {
    return _min_pitch;
}

int     MidiSettings::get_num_vel() {
    return _num_vel;
}

void    MidiSettings::set_pedal(bool pedal) {
    _pedal = pedal;
}

bool    MidiSettings::is_pedal() {
    return _pedal;
}

int     MidiSettings::get_window_width() {
    return _window_width;
}

int     MidiSettings::get_window_height() {
    return _window_height;
}

int     MidiSettings::get_window_depth() {
    return _window_height;
}

float   MidiSettings::get_velocity_height() {
    return _velocity_height;
}

float   MidiSettings::get_key_width() {
    return _key_width;
}

float MidiSettings::calc_x_by_pitch(int pitch) {
    return (pitch - get_min_pitch()) * get_key_width();
}

float   MidiSettings::calc_y_by_velocity(int velocity) {
    return get_window_height() - static_cast<float>(velocity) * get_velocity_height();
}

void    MidiSettings::set_data_path(const char * data_path) {
    _data_path.append(data_path);
}

const string & MidiSettings::get_data_path() {
    return _data_path;
}
