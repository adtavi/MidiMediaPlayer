//
//  MidiNoteParticles.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#pragma once

#include "Base.hpp"
#include "Particle.hpp"

namespace MidiGlobal {

class Particles: private vector<Particle>, public Base {
    static constexpr int    _num_particles = 5000;
    
public:
    Particles(int width, int height);
    
    virtual void        midiNoteOn() override;
    virtual void        midiNoteOff() override;
    virtual void        midiControlChange() override;
    virtual void        update() override;
    virtual void        draw() override;
    virtual bool        toDelete() const override;
    virtual void        windowResized(int width, int height) override;
};
 
}
