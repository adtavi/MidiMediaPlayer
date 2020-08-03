//
//  MidiNoteDecoratorModel.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteDecoratorModel.hpp"

MidiNoteDecoratorModel::MidiNoteDecoratorModel(MidiNoteBase* midi_note, ofNode * node) : MidiNoteDecorator(midi_note) {
    //Look at
    _look_at_node = node;
    
    // @TODO: Remove relative path
    if (ofxAssimpModelLoader::loadModel(MidiSettings::get_data_path() + "Starmie/pm0121_00.dae")) {
        init();
    }
}

void    MidiNoteDecoratorModel::init() {
    // scale
    float scale = get_scale();
    setScale(scale, scale, scale);
    
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    if (_look_at_node == nullptr) {
        setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), _max_y, 0);
    } else {
        setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), _max_y, -MidiSettings::get_window_depth() / 2);
        look_at_node();
    }
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
    
    if (_look_at_node != nullptr)
        look_at_node();
    
    setRotation(_rot_angle_index, getRotationAngle(_rot_angle_index) + _angle_rate, 0.f, 1.f, 0.f);
    _midi_note->update();
}

void    MidiNoteDecoratorModel::draw() {
    drawFaces();
    _midi_note->draw();
}

void    MidiNoteDecoratorModel::window_resized() {
    _max_y = MidiSettings::calc_y_by_velocity(_midi_note->get_velocity());
    setPosition(MidiSettings::calc_x_by_pitch(_midi_note->get_pitch()), getPosition().y, getPosition().z);
    
    float scale = get_scale();
    setScale(scale, scale, scale);

    if (_look_at_node != nullptr)
        look_at_node();
    
    _midi_note->window_resized();
}

float    MidiNoteDecoratorModel::get_scale() {
    return _window_to_scale_ratio * MidiSettings::get_window_height() * MidiSettings::get_window_width();
}

void    MidiNoteDecoratorModel::look_at_node() {
    glm::vec3 look_at_position = _look_at_node->getPosition();
    glm::vec3 rel_position = (getPosition() - look_at_position);
    auto radius = glm::length(rel_position);
    if(radius > 0){
        float latitude = glm::degrees(acos(rel_position.y / radius) - glm::half_pi<float>());
        float longitude = glm::degrees(atan2(rel_position.x , rel_position.z));
        
        setRotation(0, latitude, 1, 0, 0);
        setRotation(1, longitude, 0, 1, 0);
        setRotation(2, 0.f, 0, 0, 1);
    }
}
