//
//  MidiNoteParticles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "Particles.hpp"

using namespace MidiNoteGlobal;

Particles::Particles(int width, int height) : Base(width, height) {
    resize(_num_particles);
    for_each(begin(), end(), bind(mem_fn(&MidiNoteParticle::init), placeholders::_1, width, height));
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
    for_each(begin(), end(), mem_fn(&MidiNoteParticle::update));
}

void    Particles::draw() {
    for_each(begin(), end(), mem_fn(&MidiNoteParticle::draw));
}

bool    Particles::toDelete() const {
    return false;
}

void    Particles::windowResized(int width, int height) {
    for_each(begin(), end(), bind(mem_fn(&MidiNoteParticle::windowResized), placeholders::_1, width, height));
}
