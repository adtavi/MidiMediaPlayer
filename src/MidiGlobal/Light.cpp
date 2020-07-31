//
//  MidiNoteGlobalLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//

#include "Light.hpp"

using namespace MidiGlobal;

Light::Light() {
    _num_keys = 0;
    setAmbientColor(ofColor(0, 31, 31));
    setDiffuseColor(ofColor(0, 31, 31));
    setPosition(MidiSettings::getWindowWidth()/2, 0, 0);
    setPointLight();
    
    _constant_attenuation_rate = (_max_constant_attenuation - _min_constant_attenuation) / 20;
    _linear_attenuation_rate = (_max_linear_attenuation - _min_linear_attenuation) / 20;
}

void    Light::midiNoteOn() {
    _constant_attenuation = _min_constant_attenuation;
    _linear_attenuation = _min_linear_attenuation;
    setAttenuation(_constant_attenuation, _linear_attenuation);
    
    _num_keys++;
    enable();
}

void    Light::midiNoteOff() {
    _num_keys--;
    
    // If there are no keys pressed, disable light
    if (_num_keys == 0) {
        disable();
    }
}

void    Light::midiControlChange() {
    return;
}

void    Light::update() {
    if (_constant_attenuation < _max_constant_attenuation) {
        _constant_attenuation += _constant_attenuation_rate;
    }
    
    if (_linear_attenuation < _max_linear_attenuation) {
        _linear_attenuation += _linear_attenuation_rate;
    }
    
    setAttenuation(_constant_attenuation, _linear_attenuation);
}

void    Light::draw() {
    return;
}

bool    Light::toDelete() const {
    return false;
}

void    Light::windowResized() {
    setPosition(MidiSettings::getWindowWidth()/2, 0, 0);
}
