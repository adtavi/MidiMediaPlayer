//
//  MidiNoteParticles.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "MidiNoteGlobal.hpp"
#include "MidiNoteParticle.hpp"

class MidiNoteGlobalParticles: private std::vector<MidiNoteParticle>, public MidiNoteGlobal {
    static constexpr int    _num_particles = 5000;
    
public:
    MidiNoteGlobalParticles(int width, int height);
    
    virtual void        midiNoteOn() override;
    virtual void        midiNoteOff() override;
    virtual void        midiControlChange() override;
    virtual void        update() override;
    virtual void        draw() override;
    virtual bool        toDelete() const override;
    virtual void        windowResized(int width, int height) override;
};
