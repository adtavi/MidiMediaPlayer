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
    virtual void    windowResized() override;
};

}
