//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteLight.hpp"

MidiNoteLight::MidiNoteLight(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor::red;
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * ofGetWidth() / MidiNote::_num_keys, ofGetHeight() - (_midi_note->getVelocity() + 35) * ofGetHeight()/MidiNote::_num_vel, 0);

    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->getVelocity()/500);
    setSpotlight(15.f, 0);
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
    enable();
    _midi_note->newPress(velocity);
}

void    MidiNoteLight::update() {
    _midi_note->update();
}

void    MidiNoteLight::draw() {
    _midi_note->draw();
}
