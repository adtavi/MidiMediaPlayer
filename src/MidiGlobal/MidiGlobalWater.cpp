//
//  MidiGlobalWater.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "MidiGlobalWater.hpp"

MidiGlobalWater::MidiGlobalWater() : MidiGlobalBase() {
//    setWidth(MidiSettings::get_window_width()*2);
//    setHeight(MidiSettings::get_window_depth()*2);
//    setPosition(MidiSettings::get_window_width()/2, MidiSettings::get_window_height(), -MidiSettings::get_window_depth());
//    setOrientation(glm::vec3(90, 0, 0));
    
//    setup(MidiSettings::get_window_width(), MidiSettings::get_window_height());
//
//    disturb(MidiSettings::get_window_width()/2, MidiSettings::get_window_height()/2, 500,128);
}

void    MidiGlobalWater::midi_note_on() {
    
}
void    MidiGlobalWater::midi_note_off()  {
}

void    MidiGlobalWater::midi_control_change() {
}

void    MidiGlobalWater::update(uint64_t delta_pedal, uint64_t time_since_update)  {
//    ofxWaterRipple::update();
}

void    MidiGlobalWater::draw()  {
//    ofxWaterRipple::draw(true);
}

bool    MidiGlobalWater::to_delete() const  {
    return false;
}

void    MidiGlobalWater::window_resized()  {
    //setup(MidiSettings::get_window_width(), MidiSettings::get_window_height());
}
