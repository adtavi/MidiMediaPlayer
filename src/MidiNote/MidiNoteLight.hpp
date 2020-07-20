//
//  MidiNoteLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofMain.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteLight: public ofLight, public MidiNoteDecorator {
private:
    static float    _key_width;         // Amount of width for each key
    ofColor         _color;
    
public:
    MidiNoteLight(MidiNote * midi_note);
    
    static void     setFrame(int width, int height);
    
    virtual bool    toDelete() const override;
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};
