//
//  MidiNoteDecorator.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "Decorator.hpp"

using namespace MidiNote;

Decorator::Decorator(Base* midi_note) : _midi_note(midi_note) {}

Decorator::~Decorator() {
    delete _midi_note;
}

bool    Decorator::isOn() const {
    return _midi_note->isOn();
}

int     Decorator::getPitch() const {
    return _midi_note->getPitch();
}

int     Decorator::getVelocity() const {
    return _midi_note->getVelocity();
}

int     Decorator::getWindowWidth() const {
    return _midi_note->getWindowWidth();
}

int     Decorator::getWindowHeight() const {
    return _midi_note->getWindowHeight();
}
