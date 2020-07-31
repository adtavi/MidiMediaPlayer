//
//  MidiNoteSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "DecoratorSphere.hpp"

using namespace MidiNote;

ofColor DecoratorSphere::_base_color = ofColor(62, ofRandom( 0, 127 ), ofRandom(200,255));

DecoratorSphere::DecoratorSphere(Base* midi_note) : Decorator(midi_note) {
    _color = _base_color;
    
    _velocity_height = _midi_note->getWindowHeight() / MidiNote::_num_vel;
    _key_width = _midi_note->getWindowWidth() / MidiNote::_num_keys;
    
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * _key_width, _midi_note->getWindowHeight(), 0);
    
    _min_y = _midi_note->getWindowHeight() - (_midi_note->getVelocity() + 28) * _velocity_height;
    _threshold = _midi_note->getWindowHeight() - 28 * _velocity_height;
    _decrease_y = true;
        
    // Radius relative to window width and velocity
    setRadius(_key_width/2 + (_key_width/2) * (_midi_note->getVelocity()/100));
    
    // Material
    setAmbientColor(_color);
    setDiffuseColor(_color);
    setSpecularColor(ofFloatColor::red);
    setShininess(12);
}

void DecoratorSphere::updateGlobal() {
    //_base_color.r = (_base_color.r + 1) % 62;
    _base_color.g = (_base_color.g + 1) % 127;
    _base_color.b = 200 + (_base_color.b - 199) % 55;
}

bool    DecoratorSphere::toDelete() const {
    return getY() > _midi_note->getWindowHeight() && _midi_note->toDelete();
}

void  DecoratorSphere::setOff() {
    _midi_note->setOff();
    _decrease_y = false;
}

void  DecoratorSphere::newPress(int velocity) {
    _midi_note->newPress(velocity);
    
    _min_y = _midi_note->getWindowHeight() - _midi_note->getVelocity() * _velocity_height;
    _decrease_y = getY() > _min_y;
    
    setRadius(_key_width/2 + (_key_width/2) * (_midi_note->getVelocity()/100));
}

void DecoratorSphere::update() {
    _midi_note->update();
    
    // Moving...
    float amount = 0.f;
    
    if (_decrease_y) { // Moving upwards
        amount = -10 * _velocity_height;
        _decrease_y = getY() > _min_y;
    } else {
        if (MidiNote::isPedal() || _midi_note->isOn()) {
            
            if (getY() > _midi_note->getWindowHeight() - 28 * _velocity_height) { // threshold
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

void  DecoratorSphere::draw() {
    begin();
    ofSpherePrimitive::draw();
    end();
    _midi_note->draw();
}

void    DecoratorSphere::windowResized(int width, int height) {
    _velocity_height = height / MidiNote::_num_vel;
    _key_width = width / MidiNote::_num_keys;
    
    float y = getY() * height / _midi_note->getWindowHeight();  // Relative y to the new height
    setPosition((_midi_note->getPitch() - MidiNote::_min_pitch) * _key_width, y, 0);
    
    _min_y = height - (_midi_note->getVelocity() + 28) * _velocity_height;
    _threshold = height - 28 * _velocity_height;
    
    // New size
    setRadius(_key_width/2 + (_key_width/2) * (_midi_note->getVelocity()/100));

    _midi_note->windowResized(width, height);
}
