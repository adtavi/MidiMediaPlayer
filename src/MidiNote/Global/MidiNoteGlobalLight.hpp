//
//  MidiNoteGlobalLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "ofAppRunner.h"
#include "ofLight.h"
#include "MidiNoteGlobal.hpp"

class MidiNoteGlobalLight: private ofLight, public MidiNoteGlobal {
    
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
    MidiNoteGlobalLight();
    
    virtual void        midiNoteOn();
    virtual void        midiNoteOff();
    virtual void        midiControlChange();
    
    virtual void        update();
    virtual void        draw();
    virtual bool        toDelete() const;
};
