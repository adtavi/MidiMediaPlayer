//
//  MidiNoteSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "MidiNoteSphere.hpp"

float MidiNoteSphere::_key_width = 0.f;
float MidiNoteSphere::_velocity_height = 0.f;
float MidiNoteSphere::_threshold = 0.f;

MidiNoteSphere::MidiNoteSphere(MidiNote * midi_note, const ofColor & color) : MidiNoteDecorator(midi_note) {
    _color = color;
    setPosition((_midi_note->getPitch() - 21) * _key_width, _frame_height, 0);
    _min_y = _frame_height - (_midi_note->getVelocity() + 28) * _velocity_height;
    _threshold = _frame_height - 28 * _velocity_height;
    _decrease_y = true;

    setRadius(_midi_note->getVelocity() / 10 + 5.f);
}

void MidiNoteSphere::setFrame(int width, int height) {
    _key_width = width / 87;
    _velocity_height = height / 127;
    MidiNoteDecorator::setFrame(width, height);
}

ofColor MidiNoteSphere::getColor() const {
    return _color;
}

bool    MidiNoteSphere::toDelete() const {
    return getY() > _frame_height && _midi_note->toDelete();
}

bool  MidiNoteSphere::toDraw() const {
    return true;
}

void  MidiNoteSphere::setOff() {
    _midi_note->setOff();
    _decrease_y = false;
}

void  MidiNoteSphere::newPress(int velocity) {
    _midi_note->newPress(velocity);

    _min_y = _frame_height - _midi_note->getVelocity() * _velocity_height;
    _decrease_y = getY() > _min_y;
    
    setRadius(_midi_note->getVelocity() / 10 + 5.f);
}

void MidiNoteSphere::update() {
    _midi_note->update();
    
    float amount = 0.f;
    
     if (_decrease_y) { // Moving upwards
        amount = -10 * _velocity_height;
        _decrease_y = getY() > _min_y;
     } else {
        if (_midi_note->isPedal() || _midi_note->isOn()) {
            
            if (getY() > _frame_height - 28 * _velocity_height) { // threshold
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
    ofSpherePrimitive::draw();
    _midi_note->draw();
}
