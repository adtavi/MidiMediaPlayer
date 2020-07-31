//
//  MidiSettings.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 31/07/2020.
//

#include "MidiSettings.hpp"

bool    MidiSettings::_pedal = false;       // Whether the pedal is being pressed
int     MidiSettings::_window_width = 0;    // Window width
int     MidiSettings::_window_height = 0;   // Window height
float   MidiSettings::_velocity_height = 0; // Amount of height for each velocity value
float   MidiSettings::_key_width = 0;       // Window width for each key

void    MidiSettings::setWindow(int width, int height) {
    _window_width = width;
    _window_height = height;
    _velocity_height = height / _num_vel;
    _key_width = width / _num_keys;
}

int     MidiSettings::getNumKeys() {
    return _num_keys;
}

int     MidiSettings::getMinPitch() {
    return _min_pitch;
}

int     MidiSettings::getNumVel() {
    return _num_vel;
}

void    MidiSettings::setPedal(bool pedal) {
    return _pedal;
}

bool    MidiSettings::isPedal() {
    return _pedal;
}

int     MidiSettings::getWindowWidth() {
    return _window_width;
}

int     MidiSettings::getWindowHeight() {
    return _window_height;
}

float   MidiSettings::getVelocityHeight() {
    return _velocity_height;
}

float   MidiSettings::getKeyWidth() {
    return _key_width;
}

float   MidiSettings::calcYByVelocity(int velocity) {
    return getWindowHeight() - velocity * MidiSettings::getVelocityHeight();
}
