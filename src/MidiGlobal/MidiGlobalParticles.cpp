//
//  MidiGlobalParticles.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 22/07/2020.
//
#include "MidiGlobalParticles.hpp"

MidiGlobalParticles::MidiGlobalParticles() {
    for (int i = 0; i < _num_particles; i++)
        _particles.push_back(std::move(make_unique<MidiGlobalParticle>()));
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

void    MidiGlobalParticles::update(uint64_t delta_pedal, uint64_t time_since_update) {
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
