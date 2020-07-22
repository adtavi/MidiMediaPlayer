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

    loadModel();
}

bool    MidiNoteModel::toDelete() const {
    return _midi_note->toDelete();
}

void    MidiNoteModel::setOff() {
    _midi_note->setOff();
}

void    MidiNoteModel::newPress(int velocity) {
    loadModel();
    _midi_note->newPress(velocity);
}

void    MidiNoteModel::update() {
    _angle = fmod(_angle + 1.f, 360.f);
    setRotation(1, _angle, 0.f, 1.f, 0.f);
    _midi_note->update();
}

void    MidiNoteModel::draw() {
    drawFaces();
    _midi_note->draw();
}

void    MidiNoteModel::loadModel() {
    // @TODO: Remove relative path
    if (ofxAssimpModelLoader::loadModel("../../src/Starmie/pm0121_00.dae"), true) {
        setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * ofGetWidth() / MidiNote::_num_keys, ofGetHeight() - (_midi_note->getVelocity() + 35) * ofGetHeight()/MidiNote::_num_vel, 0);
        setScale(.05f, .05f, .05f);
        setRotation(0, 180.f, 1.f, 0.f, 0.f);
    }
}
