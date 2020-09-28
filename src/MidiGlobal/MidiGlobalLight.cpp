//
//  MidiGlobalLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//

#include "MidiGlobalLight.hpp"

MidiGlobalLight::MidiGlobalLight() {
    setAmbientColor(ofColor(0, 31, 31));
    setDiffuseColor(ofColor(0, 31, 31));
    setPosition(MidiSettings::get_window_width()/2, 0, 0);
    setPointLight();
    disable();
}

void    MidiGlobalLight::midi_note_on() {
    return;
}

void    MidiGlobalLight::midi_note_off() {
    return;
}

void    MidiGlobalLight::midi_control_change() {
    return;
}

void    MidiGlobalLight::update(uint64_t delta_pedal, uint64_t time_since_update) {
    // delta > 0 => Pedal's been pressed
    // _last_delta == 0 => First pedal
    // _last_delta != delta => Delta changed (pedal's been pressed again)
    if (delta_pedal > 0 && (_delta == 0 || _delta != delta_pedal)) {
        _delta = delta_pedal;
        _delta_acc = _delta;
        _dimming = true;
        setAttenuation(_min_constant_attenuation, _min_linear_attenuation);
        enable();
    } else if (delta_pedal == 0) {
        disable();
    } else if (_dimming) { // If it's dimming
        
        if (_delta_acc < time_since_update) {
            _delta_acc = _delta - (time_since_update - _delta_acc);
        } else {
            _delta_acc = _delta_acc - time_since_update;
        }
        
        float percentage = static_cast<float>(_delta_acc) / static_cast<float>(_delta);
        float constant_attenuation = _max_constant_attenuation - (_max_constant_attenuation - _min_constant_attenuation) * percentage;
        float linear_attenuation = _max_linear_attenuation - (_max_linear_attenuation - _min_linear_attenuation) * percentage;
        
        setAttenuation(constant_attenuation, linear_attenuation);
    }
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

void    MidiGlobalLight::disable() {
    _delta = 0;
    _delta_acc = 0;
    _dimming = false;
    ofLight::disable();
}
