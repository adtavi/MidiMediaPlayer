//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteLight.hpp"

float MidiNoteLight::_key_width = 0.f;

MidiNoteLight::MidiNoteLight(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor(255, 0, 0);
    setPosition((_midi_note->getPitch() - 21) * _key_width, 0, 0);
    
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(2.f - _midi_note->getVelocity()/100, 0.f, 0.f);
    setSpotlight(3.f, .5f);

    lookAt(glm::vec3(getX(), _frame_height, 0));
    enable();
}

void MidiNoteLight::setFrame(int width, int height) {
    _key_width = width / 87;
    MidiNoteDecorator::setFrame(width, height);
}

bool    MidiNoteLight::toDelete() const {
    return _midi_note->toDelete();
}

void  MidiNoteLight::setOff() {
    disable();
    _midi_note->setOff();
}

void  MidiNoteLight::newPress(int velocity) {
    enable();
    _midi_note->newPress(velocity);
}

void MidiNoteLight::update() {
    _midi_note->update();
}

void  MidiNoteLight::draw() {
    ofSetColor(_color);
    _midi_note->draw();
}
