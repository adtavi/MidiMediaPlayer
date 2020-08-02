//
//  MidiNoteDecoratorSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteDecoratorSphere.hpp"

ofColor MidiNoteDecoratorSphere::_base_color = ofColor(62, ofRandom(0, 127), ofRandom(200, 255));

MidiNoteDecoratorSphere::MidiNoteDecoratorSphere(MidiNoteBase* midi_note) : MidiNoteDecorator(midi_note) {
    _color = _base_color;
    
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), MidiSettings::get_window_height(), 0);
    
    _min_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    _decrease_y = true;
        
    // Radius relative to window width and velocity
    setRadius(calc_radius_by_velocity(_midi_note->get_velocity()));
    
    // Material
    setAmbientColor(_color);
    setDiffuseColor(_color);
    setSpecularColor(ofFloatColor::red);
    setShininess(12);
}

void    MidiNoteDecoratorSphere::update_global() {
    //_base_color.r = (_base_color.r + 1) % 62;
    _base_color.g = (_base_color.g + 1) % 127;
    _base_color.b = 200 + (_base_color.b - 199) % 55;
}

bool    MidiNoteDecoratorSphere::to_delete() const {
    return getY() > MidiSettings::get_window_height() && _midi_note->to_delete();
}

void    MidiNoteDecoratorSphere::set_off() {
    _decrease_y = false;
    _midi_note->set_off();
}

void    MidiNoteDecoratorSphere::new_press(int velocity) {
    _min_y = MidiSettings::calc_y_by_velocity(velocity);
    _decrease_y = getY() > _min_y;
    
    setRadius(calc_radius_by_velocity(velocity));
    
    _midi_note->new_press(velocity);
}

void    MidiNoteDecoratorSphere::update() {
    // Moving...
    float amount = 0.f;
        
    if (_decrease_y) { // Moving upwards
        amount = -_y_vel_fast * MidiSettings::get_velocity_height();
        _decrease_y = getY() > _min_y;
    } else {
        if (MidiSettings::is_pedal() || _midi_note->is_on()) {
            amount = _y_vel_slow * MidiSettings::get_velocity_height();
        }
        else {
            amount = _y_vel_fast * MidiSettings::get_velocity_height();
        }
    }
    
    boom(amount);

    _midi_note->update();
}

void    MidiNoteDecoratorSphere::draw() {
    begin();
    ofSpherePrimitive::draw();
    end();
    _midi_note->draw();
}

void    MidiNoteDecoratorSphere::window_resized() {
    _min_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), _min_y, 0);
    // New size
    setRadius(calc_radius_by_velocity(_midi_note->get_velocity()));

    _midi_note->window_resized();
}

float    MidiNoteDecoratorSphere::calc_radius_by_velocity(int velocity) {
        return MidiSettings::get_key_width()/2 + (MidiSettings::get_key_width()/2) * (velocity/100);
}
