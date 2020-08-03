//
//  MidiNoteDecoratorModel.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#pragma once

#include "ofxAssimpModelLoader.h"
#include "MidiNoteDecorator.hpp"
#include "ofNode.h"

class MidiNoteDecoratorModel: public ofxAssimpModelLoader, public MidiNoteDecorator {
    friend class    TestMidiNoteDecoratorModel;

    static constexpr float  _boom_rate = 5.0f;
    static constexpr float  _angle_rate = 5.0f;
    static constexpr float  _window_to_scale_ratio = 0.0000001;
    static constexpr int    _rot_angle_index = 3;
    
    float                   _max_y;
    ofNode*                 _look_at_node;

    void                    init();
    float                   get_scale();
    void                    look_at_node();
    
public:
    MidiNoteDecoratorModel(MidiNoteBase* midi_note, ofNode * node = nullptr);
    
    virtual bool    to_delete() const override;
    virtual void    set_off() override;
    virtual void    new_press(int velocity) override;
    virtual void    update() override;
    virtual void    draw() override;
    virtual void    window_resized() override;
};
