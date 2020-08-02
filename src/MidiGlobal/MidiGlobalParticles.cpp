//
//  MidiGlobalParticles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "MidiGlobalParticles.hpp"

MidiGlobalParticles::MidiGlobalParticles() {
    _particles.resize(_num_particles);
    for_each(_particles.begin(), _particles.end(), mem_fn(&MidiGlobalParticle::init));
}

void    MidiGlobalParticles::midi_note_on() {
    return;
}

void    MidiGlobalParticles::midi_note_off() {
    return;
}

void    MidiGlobalParticles::midi_control_change() {
    return;
}

void    MidiGlobalParticles::update() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&MidiGlobalParticle::update));
}

void    MidiGlobalParticles::draw() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&MidiGlobalParticle::draw));
}

bool    MidiGlobalParticles::to_delete() const {
    return false;
}

void    MidiGlobalParticles::window_resized() {
    for_each(_particles.begin(), _particles.end(), mem_fn(&MidiGlobalParticle::window_resized));
}
