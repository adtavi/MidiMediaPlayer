//
//  MidiNoteDecoratorLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "MidiNoteDecoratorLight.hpp"

MidiNoteDecoratorLight::MidiNoteDecoratorLight(MidiNoteBase* midi_note) : MidiNoteDecoratorLightBase(midi_note) {
    set_position();
    look_at();
}

void    MidiNoteDecoratorLight::look_at() {
    lookAt(glm::vec3(getX(), MidiSettings::get_window_height(), 0));
}

void    MidiNoteDecoratorLight::set_position() {
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), _max_y, 0);
}
