//
//  MidiNote.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNote.hpp"

bool    MidiNote::_pedal = false;

MidiNote::MidiNote(int pitch, int velocity) : _pitch(pitch), _velocity(velocity), _on(true) {
};

void MidiNote::setPedal(bool pedal) {
    _pedal = pedal;
}

bool    MidiNote::isPedal() {
    return _pedal;
}


