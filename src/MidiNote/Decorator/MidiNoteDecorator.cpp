//
//  MidiNoteDecorator.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteDecorator.hpp"

MidiNoteDecorator::MidiNoteDecorator(MidiNoteBase* midi_note) : _midi_note(midi_note) {}

MidiNoteDecorator::~MidiNoteDecorator() {
    delete _midi_note;
}

bool    MidiNoteDecorator::is_on() const {
    return _midi_note->is_on();
}

int     MidiNoteDecorator::get_pitch() const {
    return _midi_note->get_pitch();
}

int     MidiNoteDecorator::get_velocity() const {
    return _midi_note->get_velocity();
}
