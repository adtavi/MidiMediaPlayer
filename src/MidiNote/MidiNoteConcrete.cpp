//
//  MidiNote.cpp
//  midi_media_player
//
//  Created by Adriel Taboada on 18/07/2020.
//

#include "MidiNoteConcrete.hpp"


MidiNoteConcrete::MidiNoteConcrete(int pitch, int velocity) : MidiNote(pitch, velocity) {
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

ofColor MidiNoteConcrete::getColor() const {
    return ofColor(0.f,0.f,0.f);
}

bool    MidiNoteConcrete::toDelete() const {
    return !_on;
}

bool    MidiNoteConcrete::toDraw() const {
    return false;
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
