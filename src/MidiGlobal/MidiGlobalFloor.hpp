//
//  MidiGlobalFloor.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 03/08/2020.
//

#pragma once

#include "MidiGlobalBase.hpp"
#include "of3dPrimitives.h"
#include "ofMaterial.h"

class MidiGlobalFloor: public MidiGlobalBase, private ofPlanePrimitive, ofMaterial {
    friend class TestMidiGlobalFloor;
    
public:
    MidiGlobalFloor();
    
    virtual void                midi_note_on() override;
    virtual void                midi_note_off() override;
    virtual void                midi_control_change() override;
    virtual void                update() override;
    virtual void                draw() override;
    virtual bool                to_delete() const override;
    virtual void                window_resized() override;
};

