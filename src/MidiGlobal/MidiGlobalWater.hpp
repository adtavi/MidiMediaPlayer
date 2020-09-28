//
//  MidiGlobalWater.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#pragma once

#include "MidiGlobalBase.hpp"
//#include "ofxWaterRipple.h"

class MidiGlobalWater: public MidiGlobalBase {
public:
    MidiGlobalWater();
    
    virtual void        midi_note_on() override;
    virtual void        midi_note_off() override;
    virtual void        midi_control_change() override;
    virtual void        update(uint64_t delta_pedal, uint64_t time_since_update) override;
    virtual void        draw() override;
    virtual bool        to_delete() const override;
    virtual void        window_resized() override;
};
