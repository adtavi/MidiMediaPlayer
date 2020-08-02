//
//  Particles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "MidiGlobalParticles.hpp"

using namespace MidiGlobal;

MidiGlobalParticles::MidiGlobalParticles() {
    _particles.resize(_num_particles);
    for_each(_particles.begin(), _particles.end(), mem_fn(&Particle::init));
}

void    MidiGlobalParticles::midiNoteOn() {
    return;
}

void    MidiGlobalParticles::midiNoteOff() {
    return;
}

void    MidiGlobalParticles::midiControlChange() {
    return;
}

void    MidiGlobalParticles::update() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&Particle::update));
}

void    MidiGlobalParticles::draw() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&Particle::draw));
}

bool    MidiGlobalParticles::toDelete() const {
    return false;
}

unsigned int    MidiGlobalParticles::size() const {
    return _particles.size();
}

void    MidiGlobalParticles::windowResized() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&Particle::windowResized));
}
