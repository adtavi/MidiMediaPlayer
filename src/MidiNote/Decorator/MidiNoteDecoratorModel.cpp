//
//  MidiNoteDecoratorModel.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteDecoratorModel.hpp"

MidiNoteDecoratorModel::MidiNoteDecoratorModel(MidiNoteBase* midi_note) : MidiNoteDecorator(midi_note) {    
    // @TODO: Remove relative path
    if (ofxAssimpModelLoader::loadModel("../../data/Starmie/pm0121_00.dae")) {
        init();
    }
}

void    MidiNoteDecoratorModel::init() {
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), _max_y, 0);

    float scale = get_scale();
    setScale(scale, scale, scale);
}

bool    MidiNoteDecoratorModel::to_delete() const {
    return _midi_note->to_delete();
}

void    MidiNoteDecoratorModel::set_off() {
    _midi_note->set_off();
}

void    MidiNoteDecoratorModel::new_press(int velocity) {
    _max_y = MidiSettings::calc_y_by_velocity(velocity);
    _midi_note->new_press(velocity);
}

void    MidiNoteDecoratorModel::update() {
    ofPoint position = getPosition();
    
    if (position.y > _max_y + _boom_rate) {
        setPosition(position.x, position.y-_boom_rate, position.z);
    } else if (position.y < _max_y - _boom_rate) {
        setPosition(position.x, position.y+_boom_rate, position.z);
    }
    
    setRotation(1, getRotationAngle(1) + _angle_rate, 0.f, 1.f, 0.f);
    _midi_note->update();
}

void    MidiNoteDecoratorModel::draw() {
    drawFaces();
    _midi_note->draw();
}

void    MidiNoteDecoratorModel::window_resized() {
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), getPosition().y, 0);
    
    float scale = get_scale();
    setScale(scale, scale, scale);
    
    _midi_note->window_resized();
}

float    MidiNoteDecoratorModel::get_scale() {
    return _window_to_scale_ratio * MidiSettings::get_window_height() * MidiSettings::get_window_width();
}
