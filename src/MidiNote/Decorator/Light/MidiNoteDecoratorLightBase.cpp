//
//  MidiNoteDecoratorLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteDecoratorLightBase.hpp"

MidiNoteDecoratorLightBase::MidiNoteDecoratorLightBase(MidiNoteBase* midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor::red;
    
    // Color
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->get_velocity()/500);
    setSpotlight(_max_angle, 0);
    
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    
    enable();
}

bool    MidiNoteDecoratorLightBase::to_delete() const {
    return _midi_note->to_delete();
}

void    MidiNoteDecoratorLightBase::set_off() {
    disable();
    _midi_note->set_off();
}

void    MidiNoteDecoratorLightBase::new_press(int velocity) {
    _max_y = MidiSettings::calc_y_by_velocity(velocity);
    setSpotlight(_max_angle, 0);
    enable();
    _midi_note->new_press(velocity);
}

void    MidiNoteDecoratorLightBase::update() {
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
    
    look_at();
    
    _midi_note->update();
}

void    MidiNoteDecoratorLightBase::draw() {
    _midi_note->draw();
}

void    MidiNoteDecoratorLightBase::window_resized() {
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    glm::vec3 position = getPosition();
    set_position();
    setPosition(getPosition().x, position.y, getPosition().z);  // Keep the previous y position
    look_at();
    
    _midi_note->window_resized();
}
