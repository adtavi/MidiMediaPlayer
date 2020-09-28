//
//  MidiGlobalParticles.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "MidiGlobalBase.hpp"
#include "MidiGlobalParticle.hpp"

class MidiGlobalParticles: public MidiGlobalBase {
    friend class TestMidiGlobalParticles;
    
    static constexpr int        _num_particles = 5000;
    
    vector<unique_ptr<MidiGlobalParticle>>  _particles;
    
public:
    MidiGlobalParticles();
    
    virtual void                midi_note_on() override;
    virtual void                midi_note_off() override;
    virtual void                midi_control_change() override;
    virtual void                update(uint64_t delta_pedal, uint64_t time_since_update) override;
    virtual void                draw() override;
    virtual bool                to_delete() const override;
    virtual void                window_resized() override;
};
