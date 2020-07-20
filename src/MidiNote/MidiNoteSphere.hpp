//
//  MidiNoteSphere.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "ofMain.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteSphere: public ofSpherePrimitive, public MidiNoteDecorator {
private:
    float           _min_y;             // Maximum position y
    bool            _decrease_y;           // Ball moving upwards
    
    static float    _key_width;         // Amount of width for each key
    static float    _velocity_height;   // Amount of height for each velocity value
    static float    _threshold;
    ofColor         _color;
    static ofColor  _base_color;
    
public:
    MidiNoteSphere(MidiNote * midi_note);
    
    static void     updateGlobal();
    static void     setFrame(int width, int height);
    
    virtual bool    toDelete() const override;    
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};
