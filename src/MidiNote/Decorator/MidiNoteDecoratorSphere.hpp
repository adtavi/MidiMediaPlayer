//
//  MidiNoteDecoratorSphere.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteDecoratorSphere: public ofSpherePrimitive, public MidiNoteDecorator, public ofMaterial {
    friend class    TestMidiNoteDecoratorSphere;
    
    static constexpr float  _vel_slow = 1;
    static constexpr float  _vel_fast = 10;
    
    float           _min_y;             // Minimum y position
    bool            _decrease_y;        // Ball moving upwards
    ofColor         _color;             // Ball color
    static ofColor  _base_color;        // Base random changing color


public:
    MidiNoteDecoratorSphere(MidiNoteBase* midi_note);
    
    static void     update_global();
    static float    calc_radius_by_velocity(int velocity);
    
    virtual bool    to_delete() const override;    
    virtual void    set_off() override;
    virtual void    new_press(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    window_resized() override;
};
