//
//  MidiNoteGlobalLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//

#include "MidiNoteGlobalLight.hpp"

MidiNoteGlobalLight::MidiNoteGlobalLight(int width, int height) : MidiNoteGlobal(width, height) {
    _num_keys = 0;
    setAmbientColor(ofColor(0, 31, 31));
    setDiffuseColor(ofColor(0, 31, 31));
    setPosition(_window_width/2, 0, 0);
    setPointLight();
    
    _constant_attenuation_rate = (_max_constant_attenuation - _min_constant_attenuation) / 20;
    _linear_attenuation_rate = (_max_linear_attenuation - _min_linear_attenuation) / 20;
}

void    MidiNoteGlobalLight::midiNoteOn() {
    _constant_attenuation = _min_constant_attenuation;
    _linear_attenuation = _min_linear_attenuation;
    setAttenuation(_constant_attenuation, _linear_attenuation);
    
    _num_keys++;
    enable();
}

void    MidiNoteGlobalLight::midiNoteOff() {
    _num_keys--;
    
    // If there are no keys pressed, disable light
    if (_num_keys == 0) {
        disable();
    }
}

void    MidiNoteGlobalLight::midiControlChange() {
    return;
}

void    MidiNoteGlobalLight::update() {
    if (_constant_attenuation < _max_constant_attenuation) {
        _constant_attenuation += _constant_attenuation_rate;
    }
    
    if (_linear_attenuation < _max_linear_attenuation) {
        _linear_attenuation += _linear_attenuation_rate;
    }
    
    setAttenuation(_constant_attenuation, _linear_attenuation);
}

void    MidiNoteGlobalLight::draw() {
    return;
}

bool    MidiNoteGlobalLight::toDelete() const {
    return false;
}

void    MidiNoteGlobalLight::windowResized(int width, int height) {
    _window_width = width;
    _window_height = height;

    setPosition(_window_width/2, 0, 0);
}
