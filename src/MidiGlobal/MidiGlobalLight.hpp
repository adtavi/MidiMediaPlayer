//
//  MidiGlobalLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "ofLight.h"
#include "MidiGlobalBase.hpp"

class MidiGlobalLight: private ofLight, public MidiGlobalBase {
    friend class TestMidiGlobalLight;
    
    int                     _num_keys;
    
    float                   _constant_attenuation;
    static constexpr float  _min_constant_attenuation = .5f;
    static constexpr float  _max_constant_attenuation = 1.f;
    float                   _constant_attenuation_rate;
    
    float                   _linear_attenuation;
    static constexpr float  _min_linear_attenuation = 0.001f;
    static constexpr float  _max_linear_attenuation = 0.01f;
    float                   _linear_attenuation_rate;
    
public:
    MidiGlobalLight();
    
    virtual void        midi_note_on() override;
    virtual void        midi_note_off() override;
    virtual void        midi_control_change() override;
    virtual void        update() override;
    virtual void        draw() override;
    virtual bool        to_delete() const override;
    virtual void        window_resized() override;
};
