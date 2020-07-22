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
    MidiNoteGlobalParticles();
    
    virtual void        midiNoteOn();
    virtual void        midiNoteOff();
    virtual void        midiControlChange();

    virtual void        update();
    virtual void        draw();
    virtual bool        toDelete() const;

};
