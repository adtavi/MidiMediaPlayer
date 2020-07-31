//
//  MidiNote.cpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNote.hpp"

//using FooNSAlias = Foo;//alias

MidiNote::MidiNote::MidiNote(int pitch, int velocity, int width, int height) : Base() {
    _pitch = pitch;
    _velocity = velocity;
    _on = true;
    _window_width = width;
    _window_height = height;
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

void    MidiNote::MidiNote::windowResized(int width, int height) {
    _window_width = width;
    _window_height = height;
    return;
}

int     MidiNote::MidiNote::getWindowWidth() const {
    return _window_width;
}

int     MidiNote::MidiNote::getWindowHeight() const {
    return _window_height;
}
