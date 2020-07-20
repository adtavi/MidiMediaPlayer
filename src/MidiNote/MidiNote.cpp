//
//  MidiNote.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNote.hpp"

bool    MidiNote::_pedal = false;

void    MidiNote::setPedal(bool pedal) {
    _pedal = pedal;
}

bool    MidiNote::isPedal() {
    return _pedal;
}


