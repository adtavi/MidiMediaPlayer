//
//  MidiNoteDecorator.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofLight.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteDecoratorLight: public ofLight, public MidiNoteDecorator {
    friend class    TestMidiNoteDecoratorLight;

    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _max_angle = 20.f;
    static constexpr float  _min_angle = 10.f;
    static constexpr float  _angle_rate = .25f;
    
    ofColor                 _color;
    float                   _angle;
    float                   _max_y;
    ofNode*                 _look_at_node;
    
public:
    MidiNoteDecoratorLight(MidiNoteBase* midi_note, ofNode * node = nullptr);
        
    virtual bool    to_delete() const override;
    virtual void    set_off() override;
    virtual void    new_press(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    window_resized() override;
    
    void            look_at_node();
    void            set_position_node();

    void            look_at_no_node();
    void            set_position_no_node();
};
