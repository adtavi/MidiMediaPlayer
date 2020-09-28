//
//  MidiGlobalLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "ofLight.h"
#include "MidiGlobalBase.hpp"
#include "TimeManager.hpp"

class MidiGlobalLight: private ofLight, public MidiGlobalBase {
    friend class TestMidiGlobalLight;
        
    static constexpr float  _min_constant_attenuation = .5f;
    static constexpr float  _max_constant_attenuation = 1.f;
    
    static constexpr float  _min_linear_attenuation = 0.001f;
    static constexpr float  _max_linear_attenuation = 0.01f;

    uint64_t                _delta;
    uint64_t                _delta_acc;
    bool                    _dimming;
    
    void                    disable();
    
public:
    MidiGlobalLight();
    
    virtual void        midi_note_on() override;
    virtual void        midi_note_off() override;
    virtual void        midi_control_change() override;
    virtual void        update(uint64_t delta_pedal, uint64_t time_since_update) override;
    virtual void        draw() override;
    virtual bool        to_delete() const override;
    virtual void        window_resized() override;
};
