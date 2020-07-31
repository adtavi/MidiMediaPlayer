//
//  MidiNoteGlobalLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "ofLight.h"
#include "Base.hpp"

namespace MidiGlobal {

class Light: private ofLight, public Base {
    
    unsigned int            _num_keys;
    
    float                   _constant_attenuation;
    static constexpr float  _min_constant_attenuation = .5f;
    static constexpr float  _max_constant_attenuation = 1.f;
    float                   _constant_attenuation_rate;
    
    float                   _linear_attenuation;
    static constexpr float  _min_linear_attenuation = 0.001f;
    static constexpr float  _max_linear_attenuation = 0.01f;
    float                   _linear_attenuation_rate;
    
    
    
public:
    Light(int width, int height);
    
    virtual void        midiNoteOn() override;
    virtual void        midiNoteOff() override;
    virtual void        midiControlChange() override;
    virtual void        update() override;
    virtual void        draw() override;
    virtual bool        toDelete() const override;
    virtual void        windowResized(int width, int height) override;
};

}
