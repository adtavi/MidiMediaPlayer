//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "DecoratorLight.hpp"

using namespace MidiNote;

DecoratorLight::DecoratorLight(Base* midi_note) : Decorator(midi_note) {
    _color = ofColor::red;
    
    // Position
    _max_y = MidiSettings::calcYByVelocity(_midi_note->getVelocity());
    setPosition((_midi_note->getPitch() - MidiSettings::getMinPitch()) * MidiSettings::getKeyWidth(), _max_y, 0);
    
    // Color
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->getVelocity()/500);
    setSpotlight(_max_angle, 0);
    lookAt(glm::vec3(getX(), MidiSettings::getWindowHeight(), 0));
    
    enable();
}

bool    DecoratorLight::toDelete() const {
    return _midi_note->toDelete();
}

void    DecoratorLight::setOff() {
    disable();
    _midi_note->setOff();
}

void    DecoratorLight::newPress(int velocity) {
    _max_y = MidiSettings::calcYByVelocity(velocity);
    setSpotlight(_max_angle, 0);
    enable();
    _midi_note->newPress(velocity);
}

void    DecoratorLight::update() {
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

void    DecoratorLight::draw() {
    _midi_note->draw();
}

void    DecoratorLight::windowResized() {
    _max_y = MidiSettings::calcYByVelocity(_midi_note->getVelocity());
    setPosition((_midi_note->getPitch() - MidiSettings::getMinPitch()) * MidiSettings::getKeyWidth(), _max_y, 0);
    
    _midi_note->windowResized();
}
