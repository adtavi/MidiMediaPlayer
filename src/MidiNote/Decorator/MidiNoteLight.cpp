//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteLight.hpp"

MidiNoteLight::MidiNoteLight(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor::red;

    calcY();
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * ofGetWidth() / MidiNote::_num_keys, _max_y, 0);
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->getVelocity()/500);
    setSpotlight(_max_angle, 0);
    lookAt(glm::vec3(getX(), ofGetHeight(), 0));

    enable();
}

bool    MidiNoteLight::toDelete() const {
    return _midi_note->toDelete();
}

void    MidiNoteLight::setOff() {
    disable();
    _midi_note->setOff();
}

void    MidiNoteLight::newPress(int velocity) {
    calcY();
    setSpotlight(_max_angle, 0);
    enable();
    _midi_note->newPress(velocity);
}

void    MidiNoteLight::update() {
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

    _midi_note->update();
}

void    MidiNoteLight::draw() {
    _midi_note->draw();
}

void    MidiNoteLight::calcY() {
    _max_y = ofGetHeight() - (_midi_note->getVelocity() + 35) * ofGetHeight()/MidiNote::_num_vel;
}
