//
//  MidiNoteLight.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 20/07/2020.
//

#include "MidiNoteLight.hpp"

MidiNoteLight::MidiNoteLight(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = ofColor::red;

    // Position
    _max_y = calcMaxY(_midi_note->getWindowHeight());
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * _midi_note->getWindowWidth() / MidiNote::_num_keys, _max_y, 0);
    
    // Color
    setDiffuseColor(_color);
    setSpecularColor(_color);
    setAttenuation(1.f - _midi_note->getVelocity()/500);
    setSpotlight(_max_angle, 0);
    lookAt(glm::vec3(getX(), midi_note->getWindowHeight(), 0));

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
    _max_y = calcMaxY(_midi_note->getWindowHeight());
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

float    MidiNoteLight::calcMaxY(int window_height) {
    return window_height - (_midi_note->getVelocity() + 35) * (window_height/MidiNote::_num_vel);
}

void    MidiNoteLight::windowResized(int width, int height) {
    std::cout << typeid(this).name() << std::endl;
    _max_y = calcMaxY(height);
    float y = getY() * height / _midi_note->getWindowHeight();  // Relative y to the new height
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * width / MidiNote::_num_keys, y, 0);
    
    _midi_note->windowResized(width, height);
}
