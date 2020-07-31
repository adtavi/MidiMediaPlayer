//
//  MidiNoteModel.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "DecoratorModel.hpp"

using namespace MidiNote;

DecoratorModel::DecoratorModel(Base* midi_note) : Decorator(midi_note) {
    _color = ofColor(255, 0, 0);
    _angle  = 0.f;
    
    // @TODO: Remove relative path
    if (ofxAssimpModelLoader::loadModel("../../data/Starmie/pm0121_00.dae")) {
        //setScale(.1f, .1f, .1f);
        //setRotation(0, 180.f, 1.f, 0.f, 0.f);
        _max_y = calcMaxY(_midi_note->getWindowHeight());
        setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * _midi_note->getWindowWidth() / MidiNote::_num_keys, _max_y, 0);

        float scale = _window_to_scale_ratio * _midi_note->getWindowHeight() * _midi_note->getWindowWidth();
        setScale(scale, scale, scale);
    }
}

bool    DecoratorModel::toDelete() const {
    return _midi_note->toDelete();
}

void    DecoratorModel::setOff() {
    _midi_note->setOff();
}

void    DecoratorModel::newPress(int velocity) {
    _max_y = calcMaxY(_midi_note->getWindowHeight());
    _midi_note->newPress(velocity);
}

void    DecoratorModel::update() {
    ofPoint position = getPosition();
    
    if (position.y > _max_y + _boom_rate) {
        setPosition(position.x, position.y-_boom_rate, position.z);
    } else if (position.y < _max_y - _boom_rate) {
        setPosition(position.x, position.y+_boom_rate, position.z);
    }
    
    _angle = fmod(_angle + _angle_rate, 360.f);
    setRotation(1, _angle, 0.f, 1.f, 0.f);
    _midi_note->update();
}

void    DecoratorModel::draw() {
    drawFaces();
    _midi_note->draw();
}

float   DecoratorModel::calcMaxY(int window_height) {
    return window_height - (_midi_note->getVelocity() + 35) * (window_height/MidiNote::_num_vel);
}

void    DecoratorModel::windowResized(int width, int height) {
    _max_y = calcMaxY(height);
    float y = getPosition().y * height / _midi_note->getWindowHeight();  // Relative y to the new height
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * width / MidiNote::_num_keys, y, 0);
    
    float scale = _window_to_scale_ratio * _midi_note->getWindowHeight() * _midi_note->getWindowWidth();
    setScale(scale, scale, scale);
    
    _midi_note->windowResized(width, height);
}
