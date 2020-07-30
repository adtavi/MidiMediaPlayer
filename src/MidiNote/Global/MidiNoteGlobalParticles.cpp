//
//  MidiNoteParticles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "MidiNoteGlobalParticles.hpp"

MidiNoteGlobalParticles::MidiNoteGlobalParticles(int width, int height) : MidiNoteGlobal(width, height) {
    resize(_num_particles);
    std::for_each(begin(), end(), std::bind(std::mem_fn(&MidiNoteParticle::init), std::placeholders::_1, width, height));
}

void    MidiNoteGlobalParticles::midiNoteOn() {
    return;
}

void    MidiNoteGlobalParticles::midiNoteOff() {
    return;
}

void    MidiNoteGlobalParticles::midiControlChange() {
    return;
}

void    MidiNoteGlobalParticles::update() {
    std::for_each(begin(), end(), std::mem_fn(&MidiNoteParticle::update));
}

void    MidiNoteGlobalParticles::draw() {
    std::for_each(begin(), end(), std::mem_fn(&MidiNoteParticle::draw));
}

bool    MidiNoteGlobalParticles::toDelete() const {
    return false;
}

void    MidiNoteGlobalParticles::windowResized(int width, int height) {
    std::for_each(begin(), end(), std::bind(std::mem_fn(&MidiNoteParticle::windowResized), std::placeholders::_1, width, height));
}
