//
//  MidiNoteDecorator.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteDecorator.hpp"

int     MidiNoteDecorator::_frame_width = 0;
int     MidiNoteDecorator::_frame_height = 0;

MidiNoteDecorator::MidiNoteDecorator(MidiNote * midi_note) : _midi_note(midi_note) {}

MidiNoteDecorator::~MidiNoteDecorator() {
    delete _midi_note;
}

void    MidiNoteDecorator::setFrame(int width, int height) {
    _frame_width = width;
    _frame_height = height;
}

bool    MidiNoteDecorator::isOn() const {
    return _midi_note->isOn();
}

int     MidiNoteDecorator::getPitch() const {
    return _midi_note->getPitch();

}

int     MidiNoteDecorator::getVelocity() const {
    return _midi_note->getVelocity();
}


