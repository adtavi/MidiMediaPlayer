//
//  MidiNoteLight.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "MidiNoteDecorator.hpp"

class MidiNoteLight: public ofLight, public MidiNoteDecorator {
private:
    ofColor         _color;
    
public:
    MidiNoteLight(MidiNote * midi_note);
        
    virtual bool    toDelete() const override;
    virtual void    setOff() override;
    virtual void    newPress(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
};
