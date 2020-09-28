//
//  MidiNote.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 18/07/2020.
//
#pragma once

#include "MidiNoteBase.hpp"

class MidiNote: public MidiNoteBase {
    
private:
    int                 _pitch;             // Pitch value
    int                 _velocity;          // Velocity values
    bool                _on;                // Whether the key is still being pressed
    
public:
    MidiNote(int pitch, int velocity);
    
    virtual bool        is_on() const override;
    virtual int         get_pitch() const override;
    virtual int         get_velocity() const override;
    virtual bool        to_delete() const override;
    virtual void        set_off() override;
    virtual void        new_press(int velocity) override;
    virtual void        update(uint64_t delta_note, uint64_t time_since_update) override;
    virtual void        draw() override;
    virtual void        window_resized() override;
};
