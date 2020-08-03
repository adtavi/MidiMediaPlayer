//
//  MidiNoteDecoratorLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteDecoratorLight.hpp"

MidiNoteDecoratorLight::MidiNoteDecoratorLight(MidiNoteBase* midi_note, ofNode * node) : MidiNoteDecorator(midi_note) {
    _color = ofColor::red;
        
    // Color
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->get_velocity()/500);
    setSpotlight(_max_angle, 0);
    
    //Look at
    _look_at_node = node;
    
    if (_look_at_node == nullptr) {
        _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
        set_position_no_node();
        look_at_no_node();
    }
    else {
        set_position_node();
        look_at_node();
    }
    
    enable();
}

bool    MidiNoteDecoratorLight::to_delete() const {
    return _midi_note->to_delete();
}

void    MidiNoteDecoratorLight::set_off() {
    disable();
    _midi_note->set_off();
}

void    MidiNoteDecoratorLight::new_press(int velocity) {
    _max_y = MidiSettings::calc_y_by_velocity(velocity);
    setSpotlight(_max_angle, 0);
    enable();
    _midi_note->new_press(velocity);
}

void    MidiNoteDecoratorLight::update() {
    ofPoint position = getPosition();

    if (getY() > _max_y + _boom_rate) {
        setPosition(position.x, position.y-_boom_rate, position.z);
    } else if (position.y < _max_y - _boom_rate) {
        setPosition(position.x, position.y+_boom_rate, position.z);
    }
    
    float spotlight_cutoff = getSpotlightCutOff();
    if (getSpotlightCutOff() > _min_angle) {
        setSpotlightCutOff(spotlight_cutoff-_angle_rate);
    }
    
    if (_look_at_node == nullptr) {
        look_at_no_node();
    }
    else {
        look_at_node();
    }
    
    _midi_note->update();
}

void    MidiNoteDecoratorLight::draw() {
    _midi_note->draw();
}

void    MidiNoteDecoratorLight::window_resized() {
    if (_look_at_node == nullptr) {
        set_position_no_node();
        look_at_no_node();
    }
    else {
        set_position_node();
        look_at_node();
    }
    
    _midi_note->window_resized();
}

void    MidiNoteDecoratorLight::look_at_node() {
    lookAt(*_look_at_node);
}

void    MidiNoteDecoratorLight::set_position_node() {
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), MidiSettings::calc_y_by_velocity(_midi_note->get_velocity()), - MidiSettings::get_window_depth() / 2);
}

void    MidiNoteDecoratorLight::look_at_no_node() {
    lookAt(glm::vec3(getX(), MidiSettings::get_window_height(), 0));
}

void    MidiNoteDecoratorLight::set_position_no_node() {
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), MidiSettings::calc_y_by_velocity(_midi_note->get_velocity()), 0);
}
