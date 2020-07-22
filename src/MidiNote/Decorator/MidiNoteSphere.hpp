//
//  MidiNoteSphere.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteSphere: public ofSpherePrimitive, public MidiNoteDecorator, public ofMaterial {
private:
    float           _min_y;             // Maximum position y
    bool            _decrease_y;        // Ball moving upwards
    float           _velocity_height;   // Amount of height for each velocity value
    float           _threshold;         // Threshold for slowing down sphere falling
    ofColor         _color;             // Ball color
    static ofColor  _base_color;        // Base random changing color
    
public:
    MidiNoteSphere(MidiNote * midi_note);
    
    static void     updateGlobal();
    
    virtual bool    toDelete() const override;    
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};

