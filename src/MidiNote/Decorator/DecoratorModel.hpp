//
//  MidiNoteModel.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofxAssimpModelLoader.h"
#include "Decorator.hpp"

namespace MidiNote {

class DecoratorModel: public ofxAssimpModelLoader, public Decorator {
private:
    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _angle_rate = 5.0f;
    static constexpr float  _window_to_scale_ratio = 0.0000001;
    
    ofColor                 _color;
    float                   _angle;
    float                   _max_y;
        
public:
    DecoratorModel(Base* midi_note);
    
    virtual bool    toDelete() const override;
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    windowResized() override;
};

}
