//
//  MidiNoteLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofAppRunner.h"
#include "ofLight.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteLight: public ofLight, public MidiNoteDecorator {
private:
    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _max_angle = 20.f;
    static constexpr float  _min_angle = 10.f;
    static constexpr float  _angle_rate = .25f;
    
    ofColor                 _color;
    float                   _angle;
    float                   _max_y;
    
    void                    calcY();

public:
    MidiNoteLight(MidiNote * midi_note);
        
    virtual bool    toDelete() const override;
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};
