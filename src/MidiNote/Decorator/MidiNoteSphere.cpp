//
//  MidiNoteSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteSphere.hpp"

ofColor MidiNoteSphere::_base_color = ofColor(62, ofRandom( 0, 127 ), ofRandom(200,255));

MidiNoteSphere::MidiNoteSphere(MidiNote * midi_note) : MidiNoteDecorator(midi_note) {
    _color = _base_color;
    _velocity_height = ofGetHeight() / MidiNote::_num_vel;
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * ofGetWidth() / MidiNote::_num_keys, ofGetHeight(), 0);
    _min_y = ofGetHeight() - (_midi_note->getVelocity() + 28) * _velocity_height;
    _threshold = ofGetHeight() - 28 * _velocity_height;
    _decrease_y = true;
    
    // Radius
    setRadius(_midi_note->getVelocity() / 5 + 5.f);
    
    // Material
    setAmbientColor(_color);
    setDiffuseColor(_color);
    setSpecularColor(ofFloatColor::red);
    setShininess(12);
}

void MidiNoteSphere::updateGlobal() {
    //_base_color.r = (_base_color.r + 1) % 62;
    _base_color.g = (_base_color.g + 1) % 127;
    _base_color.b = 200 + (_base_color.b - 199) % 55;
}

bool    MidiNoteSphere::toDelete() const {
    return getY() > ofGetHeight() && _midi_note->toDelete();
}

void  MidiNoteSphere::setOff() {
    _midi_note->setOff();
    _decrease_y = false;
}

void  MidiNoteSphere::newPress(int velocity) {
    _midi_note->newPress(velocity);
    
    _min_y = ofGetHeight() - _midi_note->getVelocity() * _velocity_height;
    _decrease_y = getY() > _min_y;
    
    setRadius(_midi_note->getVelocity() / 10 + 5.f);
}

void MidiNoteSphere::update() {
    _midi_note->update();
    
    // Moving...
    float amount = 0.f;
    
    if (_decrease_y) { // Moving upwards
        amount = -10 * _velocity_height;
        _decrease_y = getY() > _min_y;
    } else {
        if (_midi_note->isPedal() || _midi_note->isOn()) {
            
            if (getY() > ofGetHeight() - 28 * _velocity_height) { // threshold
                amount = 0.5 * _velocity_height;
            } else {
                // Proportional to the distance to the threshold
                amount = (((_threshold - getY()) / _threshold) * 4.5 + 0.5 ) * _velocity_height;
            }
        }
        else {
            amount = 10 * _velocity_height;
        }
    }
    
    boom(amount);
}

void  MidiNoteSphere::draw() {
    begin();
    ofSpherePrimitive::draw();
    end();
    _midi_note->draw();
}
