//
//  MidiGlobalFloor.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 03/08/2020.
//

#include "MidiGlobalFloor.hpp"

MidiGlobalFloor::MidiGlobalFloor() {
    setWidth(MidiSettings::get_window_width()*2);
    setHeight(MidiSettings::get_window_depth()*2);
    setPosition(MidiSettings::get_window_width()/2, MidiSettings::get_window_height(), -MidiSettings::get_window_depth());
    setOrientation(glm::vec3(90, 0, 0));
    
    setAmbientColor(ofFloatColor::white);
    setDiffuseColor(ofFloatColor::white);
    setSpecularColor(ofFloatColor::white);
    setShininess(128);
}

void    MidiGlobalFloor::midi_note_on() {
    return;
}

void    MidiGlobalFloor::midi_note_off() {
    return;
}

void    MidiGlobalFloor::midi_control_change() {
    return;
}

void    MidiGlobalFloor::update(uint64_t delta_pedal, uint64_t time_since_update) {
}

void    MidiGlobalFloor::draw() {
    ofMaterial::begin();
    ofPlanePrimitive::draw();
    ofMaterial::end();
}

bool    MidiGlobalFloor::to_delete() const {
    return false;
}

void    MidiGlobalFloor::window_resized() {
    return;
}
