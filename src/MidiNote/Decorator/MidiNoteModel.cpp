//
//  MidiNoteModel.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteModel.hpp"

MidiNoteModel::MidiNoteModel(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor(255, 0, 0);
    _angle  = 0.f;
    
    // @TODO: Remove relative path
    if (ofxAssimpModelLoader::loadModel("../../Starmie/pm0121_00.dae")) {
        setScale(.1f, .1f, .1f);
        setRotation(0, 180.f, 1.f, 0.f, 0.f);
        calcY();
        setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * ofGetWidth() / MidiNote::_num_keys, _max_y, 0);
    }
}

bool    MidiNoteModel::toDelete() const {
    return _midi_note->toDelete();
}

void    MidiNoteModel::setOff() {
    _midi_note->setOff();
}

void    MidiNoteModel::newPress(int velocity) {
    calcY();
    _midi_note->newPress(velocity);
}

void    MidiNoteModel::update() {
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

void    MidiNoteModel::draw() {
    drawFaces();
    _midi_note->draw();
}

void    MidiNoteModel::calcY() {
    _max_y = ofGetHeight() - (_midi_note->getVelocity() + 35) * ofGetHeight()/MidiNote::_num_vel;
}
