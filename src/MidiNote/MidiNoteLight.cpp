//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteLight.hpp"

MidiNoteLight::MidiNoteLight(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor(255, 0, 0);
    setPosition((_midi_note->getPitch() - 21) * ofGetWidth() / 87, ofGetHeight() - (_midi_note->getVelocity() + 35) * ofGetHeight()/127, 0);

    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(2.f - _midi_note->getVelocity()*2/100, 0.f, 0.f);
    
    setSpotlight(3.f, 1.f);
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
