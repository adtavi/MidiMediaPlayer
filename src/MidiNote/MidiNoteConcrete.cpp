//
//  MidiNote.cpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNoteConcrete.hpp"

bool    MidiNoteConcrete::_pedal = false;

MidiNoteConcrete::MidiNoteConcrete(int pitch, int velocity) : MidiNote() {
    _pitch = pitch;
    _velocity = velocity;
    _on = true;
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
