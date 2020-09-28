//
//  MidiNote.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNote.hpp"

MidiNote::MidiNote(int pitch, int velocity) : MidiNoteBase() {
    _pitch = pitch;
    _velocity = velocity;
    _on = true;
}

bool    MidiNote::is_on() const {
    return _on;
}

int     MidiNote::get_pitch() const {
    return _pitch;
}

int     MidiNote::get_velocity() const {
    return _velocity;
}

bool    MidiNote::to_delete() const {
    return !_on;
}

void    MidiNote::set_off() {
    _on = false;
}

void    MidiNote::new_press(int velocity) {
    _on = true;
    _velocity = velocity;
}

void    MidiNote::update(uint64_t delta_note, uint64_t time_since_update) {
    return;
}

void    MidiNote::draw() {
    return;
}

void    MidiNote::window_resized() {
    return;
}
