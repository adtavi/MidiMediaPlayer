//
//  MidiGlobalLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//

#include "MidiGlobalLight.hpp"

MidiGlobalLight::MidiGlobalLight() {
    _num_keys = 0;
    setAmbientColor(ofColor(0, 31, 31));
    setDiffuseColor(ofColor(0, 31, 31));
    setPosition(MidiSettings::get_window_width()/2, 0, 0);
    setPointLight();
    
    _constant_attenuation = _max_constant_attenuation;
    _linear_attenuation = _max_linear_attenuation;

    _constant_attenuation_rate = (_max_constant_attenuation - _min_constant_attenuation) / 20;
    _linear_attenuation_rate = (_max_linear_attenuation - _min_linear_attenuation) / 20;
}

void    MidiGlobalLight::midi_note_on() {
    _constant_attenuation = _min_constant_attenuation;
    _linear_attenuation = _min_linear_attenuation;
    setAttenuation(_constant_attenuation, _linear_attenuation);
    
    _num_keys++;
    enable();
}

void    MidiGlobalLight::midi_note_off() {
    _num_keys = max(-_num_keys, 0);
    
    // If there are no keys pressed, disable light
    if (_num_keys == 0) {
        disable();
    }
}

void    MidiGlobalLight::midi_control_change() {
    return;
}

void    MidiGlobalLight::update() {
    if (_constant_attenuation < _max_constant_attenuation) {
        _constant_attenuation += _constant_attenuation_rate;
    }
    
    if (_linear_attenuation < _max_linear_attenuation) {
        _linear_attenuation += _linear_attenuation_rate;
    }
    
    setAttenuation(_constant_attenuation, _linear_attenuation);
}

void    MidiGlobalLight::draw() {
    return;
}

bool    MidiGlobalLight::to_delete() const {
    return false;
}

void    MidiGlobalLight::window_resized() {
    setPosition(MidiSettings::get_window_width()/2, 0, 0);
}
