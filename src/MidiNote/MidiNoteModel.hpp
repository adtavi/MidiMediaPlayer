//
//  MidiNoteModel.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteModel: public ofxAssimpModelLoader, public MidiNoteDecorator {
private:
    float           _key_width;         // Amount of width for each key
    ofColor         _color;
    float           _angle;
    
    void            loadModel();
public:
    MidiNoteModel(MidiNote * midi_note);
        
    virtual bool    toDelete() const override;
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};
