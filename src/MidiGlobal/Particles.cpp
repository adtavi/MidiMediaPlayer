//
//  MidiNoteParticles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "Particles.hpp"

using namespace MidiGlobal;

Particles::Particles() {
    resize(_num_particles);
    for_each(begin(), end(), mem_fn(&Particle::init));
}

void    Particles::midiNoteOn() {
    return;
}

void    Particles::midiNoteOff() {
    return;
}

void    Particles::midiControlChange() {
    return;
}

void    Particles::update() {
    for_each(begin(), end(), mem_fn(&Particle::update));
}

void    Particles::draw() {
    for_each(begin(), end(), mem_fn(&Particle::draw));
}

bool    Particles::toDelete() const {
    return false;
}

void    Particles::windowResized() {
    for_each(begin(), end(), mem_fn(&Particle::windowResized));
}
