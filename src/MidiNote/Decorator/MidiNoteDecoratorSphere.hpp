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
    
    static constexpr float  _vel_slow = 1;      // Slow velocity
    static constexpr float  _vel_fast = 10;     // Fast velocity
    
    ofColor                 _color;             // Ball color
    static ofColor          _base_color;        // Base random changing color
    
    float                   _min_y;             // Minimum y position
    bool                    _decrease_y;        // Ball moving upwards
    
    float                   _min_radius;        // Minimum radius
    float                   _max_radius;        // Maximum radius
    
    double                  _delta;             // Delta
    double                  _delta_acc;         // Time to complete delta
    bool                    _growing;           // Whether the sphere's radius is growing
    
    static void             update_color();
    
    tuple<float,float>      calc_radius_by_velocity(int velocity);
    void                    boom();
    void                    dolly();
    void                    set_radius(uint64_t delta_note, uint64_t time_since_update);

public:
    MidiNoteDecoratorSphere(MidiNoteBase* midi_note);
    
    
    virtual bool            to_delete() const override;
    virtual void            set_off() override;
    virtual void            new_press(int velocity) override;
    virtual void            update(uint64_t delta_note, uint64_t time_since_update) override;
    virtual void            draw() override;
    virtual void            window_resized() override;
};
