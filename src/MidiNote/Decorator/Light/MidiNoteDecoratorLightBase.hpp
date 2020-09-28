//
//  MidiNoteDecoratorLightBase.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofLight.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteDecoratorLightBase: public ofLight, public MidiNoteDecorator {
protected:
    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _max_angle = 20.f;
    static constexpr float  _min_angle = 10.f;
    static constexpr float  _angle_rate = .25f;
    
    ofColor                 _color;
    float                   _angle;
    float                   _max_y;
    
    void                    boom();
    
    virtual void            look_at() = 0;
    virtual void            set_position() = 0;
    
public:
    MidiNoteDecoratorLightBase(MidiNoteBase* midi_note);
        
    virtual bool    to_delete() const override;
    virtual void    set_off() override;
    virtual void    new_press(int velocity) override;
    virtual void    update(uint64_t delta_note, uint64_t time_since_update) override;
    virtual void    draw() override;
    virtual void    window_resized() override;
    
};
