//
//  MidiNote.cpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNote.hpp"

MidiNote::MidiNote::MidiNote(int pitch, int velocity) : Base() {
    _pitch = pitch;
    _velocity = velocity;
    _on = true;
}

bool    MidiNote::MidiNote::isOn() const {
    return _on;
}

int     MidiNote::MidiNote::getPitch() const {
    return _pitch;
}

int     MidiNote::MidiNote::getVelocity() const {
    return _velocity;
}

bool    MidiNote::MidiNote::toDelete() const {
    return !_on;
}

void    MidiNote::MidiNote::setOff() {
    _on = false;
}

void    MidiNote::MidiNote::newPress(int velocity) {
    _on = true;
    _velocity = velocity;
}

void    MidiNote::MidiNote::update() {
    return;
}

void    MidiNote::MidiNote::draw() {
    return;
}

void    MidiNote::MidiNote::windowResized() {
    return;
}
