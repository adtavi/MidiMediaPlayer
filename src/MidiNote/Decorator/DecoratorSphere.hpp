//
//  MidiNoteSphere.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include "Decorator.hpp"

namespace MidiNote {

class DecoratorSphere: public ofSpherePrimitive, public Decorator, public ofMaterial {
private:
    float           _min_y;             // Minimum y position
    bool            _decrease_y;        // Ball moving upwards
    float           _velocity_height;   // Amount of height for each velocity value
    float           _threshold;         // Threshold for slowing down sphere falling
    float           _key_width;         // Window width for each key
    ofColor         _color;             // Ball color
    static ofColor  _base_color;        // Base random changing color
    
public:
    DecoratorSphere(Base* midi_note);
    
    static void     updateGlobal();
    
    virtual bool    toDelete() const override;    
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    windowResized(int width, int height) override;
};

}
