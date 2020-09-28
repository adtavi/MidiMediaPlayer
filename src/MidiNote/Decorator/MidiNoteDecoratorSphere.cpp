//
//  MidiNoteDecoratorSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteDecoratorSphere.hpp"

ofColor MidiNoteDecoratorSphere::_base_color = ofColor(ofRandom(0, 62), ofRandom(0, 127), ofRandom(200, 255));

MidiNoteDecoratorSphere::MidiNoteDecoratorSphere(MidiNoteBase* midi_note) : MidiNoteDecorator(midi_note) {
    _color = _base_color;
    
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), MidiSettings::get_window_height(), 0);
    
    _min_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    _decrease_y = true;
    
    // Radius relative to window width and velocity
    tie(_min_radius, _max_radius) = calc_radius_by_velocity(_midi_note->get_velocity());
    setRadius(_min_radius);
    
    // Material
    setAmbientColor(_color);
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setShininess(12);
    update_color();
    
    _delta = 0;
    _delta_acc = 0;
    _growing = false;
}

void    MidiNoteDecoratorSphere::update_color() {
    _base_color.r = (_base_color.r + 1) % 62;
    _base_color.g = (_base_color.g + 1) % 127;
    _base_color.b = 200 + (_base_color.b - 199) % 55;
}

bool    MidiNoteDecoratorSphere::to_delete() const {
    return getY() > MidiSettings::get_window_height()
    || getZ() > MidiSettings::get_window_depth();
}

void    MidiNoteDecoratorSphere::set_off() {
    _decrease_y = false;
    _midi_note->set_off();
}

void    MidiNoteDecoratorSphere::new_press(int velocity) {
    _min_y = MidiSettings::calc_y_by_velocity(velocity);
    _decrease_y = getY() > _min_y;
    tie(_min_radius, _max_radius) = calc_radius_by_velocity(_midi_note->get_velocity());
    _midi_note->new_press(velocity);
}

void    MidiNoteDecoratorSphere::update(uint64_t delta_note, uint64_t time_since_update) {
    boom();
    dolly();
    set_radius(delta_note, time_since_update);
    _midi_note->update(delta_note, time_since_update);
}

void    MidiNoteDecoratorSphere::boom() {
    float boom_amount = 0.f;
            
    if (_decrease_y) { // Moving upwards
        if (getY() - _vel_fast * MidiSettings::get_velocity_height() < _min_y) {
            _decrease_y = false;
        } else {
            boom_amount = -_vel_fast * MidiSettings::get_velocity_height();
        }
    } else {
        if (MidiSettings::is_pedal() || _midi_note->is_on()) {
            boom_amount = _vel_slow * MidiSettings::get_velocity_height();
        }
        else {
            boom_amount = _vel_fast * MidiSettings::get_velocity_height();
        }
    }
    
    ofSpherePrimitive::boom(boom_amount);
}

void    MidiNoteDecoratorSphere::dolly() {
    float dolly_amount;
    
    if (MidiSettings::is_pedal() || _midi_note->is_on()) {
        dolly_amount = - _midi_note->get_velocity() / _vel_fast;
    }
    else {
        dolly_amount = -_vel_slow;
    }
    
    ofSpherePrimitive::dolly(dolly_amount);
}

void    MidiNoteDecoratorSphere::set_radius(uint64_t delta_note, uint64_t time_since_update) {
    // delta > 0 => Some keys have been pressed
    // _last_delta == 0 => First note
    // _last_delta != delta => Delta changed (some more keys have been pressed)
    if (delta_note > 0 && (_delta == 0 || _delta != delta_note)) {
        _delta = delta_note;
        _delta_acc = _delta;
        _growing = true;
        setRadius(_min_radius);
    } else if (delta_note == 0) {
        _delta = 0;
        _delta_acc = 0;
        _growing = false;
        setRadius(_min_radius);
    } else if (_growing) { // If it's growing
        if (_delta_acc < time_since_update) {
            _delta_acc = _delta - (time_since_update - _delta_acc);
        } else {
            _delta_acc = _delta_acc - time_since_update;
        }

        float percentage = static_cast<float>(_delta_acc) / static_cast<float>(_delta);
        float radius = _min_radius + (_max_radius - _min_radius) * percentage;
        setRadius(radius);
    }
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
    tie(_min_radius, _max_radius) = calc_radius_by_velocity(_midi_note->get_velocity());
    _midi_note->window_resized();
}

tuple<float,float>  MidiNoteDecoratorSphere::calc_radius_by_velocity(int velocity) {
    return make_tuple(MidiSettings::get_key_width() + MidiSettings::get_key_width() * (velocity/100.), MidiSettings::get_key_width() + 2 * MidiSettings::get_key_width() * (velocity/100.));
}
