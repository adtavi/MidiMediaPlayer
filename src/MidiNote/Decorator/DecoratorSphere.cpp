//
//  MidiNoteSphere.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 19/07/2020.
//

#include "DecoratorSphere.hpp"
#include "MidiSettings.hpp"

using namespace MidiNote;

ofColor DecoratorSphere::_base_color = ofColor(62, ofRandom(0, 127), ofRandom(200, 255));

DecoratorSphere::DecoratorSphere(Base* midi_note) : Decorator(midi_note) {
    _color = _base_color;
    
    setPosition((_midi_note->getPitch() - MidiSettings::getMinPitch()) * MidiSettings::getKeyWidth(), MidiSettings::getWindowHeight(), 0);
    
    _min_y = MidiSettings::calcYByVelocity(_midi_note->getVelocity());
    _decrease_y = true;
        
    // Radius relative to window width and velocity
    setRadius(MidiSettings::getKeyWidth()/2 + (MidiSettings::getKeyWidth()/2) * (_midi_note->getVelocity()/100));
    
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
    return getY() > MidiSettings::getWindowHeight() && _midi_note->toDelete();
}

void  DecoratorSphere::setOff() {
    _decrease_y = false;
    _midi_note->setOff();
}

void  DecoratorSphere::newPress(int velocity) {
    _min_y = MidiSettings::calcYByVelocity(_midi_note->getVelocity());
    _decrease_y = getY() > _min_y;
    
    setRadius(MidiSettings::getKeyWidth()/2 + (MidiSettings::getKeyWidth()/2) * (_midi_note->getVelocity()/100));
    
    _midi_note->newPress(velocity);
}

void DecoratorSphere::update() {
    // Moving...
    float amount = 0.f;
        
    if (_decrease_y) { // Moving upwards
        amount = -10 * MidiSettings::getVelocityHeight();
        _decrease_y = getY() > _min_y;
    } else {
        if (MidiSettings::isPedal() || _midi_note->isOn()) {
            amount = 1 * MidiSettings::getVelocityHeight();
        }
        else {
            amount = 10 * MidiSettings::getVelocityHeight();
        }
    }
    
    boom(amount);

    _midi_note->update();
}

void  DecoratorSphere::draw() {
    begin();
    ofSpherePrimitive::draw();
    end();
    _midi_note->draw();
}

void    DecoratorSphere::windowResized() {
    _min_y = MidiSettings::calcYByVelocity(_midi_note->getVelocity());
    
    setPosition((_midi_note->getPitch() - MidiSettings::getMinPitch()) * MidiSettings::getKeyWidth(), _min_y, 0);
    // New size
    setRadius(MidiSettings::getKeyWidth()/2 + (MidiSettings::getKeyWidth()/2) * (_midi_note->getVelocity()/100));

    _midi_note->windowResized();
}
