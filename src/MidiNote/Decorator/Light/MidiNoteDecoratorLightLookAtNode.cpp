//
//  MidiNoteDecoratorLightLookAtNode.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "MidiNoteDecoratorLightLookAtNode.hpp"

MidiNoteDecoratorLightLookAtNode::MidiNoteDecoratorLightLookAtNode(MidiNoteBase* midi_note, ofNode * node) : MidiNoteDecoratorLightBase(midi_note), _look_at_node(node) {
    set_position();
    look_at();
}

void    MidiNoteDecoratorLightLookAtNode::look_at() {
    lookAt(*_look_at_node);
}

void    MidiNoteDecoratorLightLookAtNode::set_position() {
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), MidiSettings::calc_y_by_velocity(_midi_note->get_velocity()), - MidiSettings::get_window_depth() / 2);
}
