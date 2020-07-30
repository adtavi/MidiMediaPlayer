//
//  MidiNote.cpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNoteConcrete.hpp"

bool    MidiNoteConcrete::_pedal = false;

MidiNoteConcrete::MidiNoteConcrete(int pitch, int velocity, int width, int height) : MidiNote() {
    _pitch = pitch;
    _velocity = velocity;
    _on = true;
    _window_width = width;
    _window_height = height;
}

bool    MidiNoteConcrete::isOn() const {
    return _on;
}

int     MidiNoteConcrete::getPitch() const {
    return _pitch;
}

int     MidiNoteConcrete::getVelocity() const {
    return _velocity;
}

bool    MidiNoteConcrete::toDelete() const {
    return !_on;
}

void    MidiNoteConcrete::setOff() {
    _on = false;
}

void    MidiNoteConcrete::newPress(int velocity) {
    _on = true;
    _velocity = velocity;
}

void    MidiNoteConcrete::update() {
    return;
}

void    MidiNoteConcrete::draw() {
    return;
}

void    MidiNoteConcrete::windowResized(int width, int height) {
    _window_width = width;
    _window_height = height;
    return;
}

int     MidiNoteConcrete::getWindowWidth() const {
    return _window_width;
}

int     MidiNoteConcrete::getWindowHeight() const {
    return _window_height;
}
