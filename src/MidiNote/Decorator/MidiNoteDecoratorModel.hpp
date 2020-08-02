//
//  MidiNoteDecoratorModel.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofxAssimpModelLoader.h"
#include "MidiNoteDecorator.hpp"

class MidiNoteDecoratorModel: public ofxAssimpModelLoader, public MidiNoteDecorator {
    friend class    TestMidiNoteDecoratorModel;

    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _angle_rate = 5.0f;
    static constexpr float  _window_to_scale_ratio = 0.0000001;
    
    float                   _max_y;
    
    void                    init();
    float                   get_scale();
    
public:
    MidiNoteDecoratorModel(MidiNoteBase* midi_note);
    
    virtual bool    to_delete() const override;
    virtual void    set_off() override;
    virtual void    new_press(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    window_resized() override;
};
