//
//  MidiNoteParticle.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#include "Particle.hpp"

using namespace MidiGlobal;

Particle::Particle() {
    // Material
    setAmbientColor(ofFloatColor::black);
    setDiffuseColor(ofFloatColor::gold);
    setSpecularColor(ofFloatColor::gold);
    setShininess(0);
}

void    Particle::init() {
    // Random velocity
    _velocity.x = ofRandom(-0.2, 0.2);
    _velocity.y = ofRandom(0, 0.6);
    _velocity.z = 0;
    
    // Initial random pos
    setPosition(rand() % MidiSettings::getWindowWidth(), rand() % MidiSettings::getWindowHeight(), 0);
    
    // Random orientation
    setOrientation(glm::vec3(rand() % 360, rand() % 360, rand() % 360));
    
    // Size
    const float size = MidiSettings::getWindowWidth() * MidiSettings::getWindowHeight() * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}

void    Particle::update() {
    // Update position
    setPosition(getPosition() + _velocity);
    
    // If it went out of screen, move it upwards
    if (getY() + _velocity.y > MidiSettings::getWindowHeight()) {
        setPosition(getX(), 0, getZ());
    }
    
    // Check if it goes out of bound for width
    if (getX() > MidiSettings::getWindowWidth()) {
        setPosition(MidiSettings::getWindowWidth(), getY(), getZ());
        _velocity.x *= -1.0;
    } else if (getX() < 0) {
        setPosition(0, getY(), getZ());
        _velocity.x *= -1.0;
    }
}

void    Particle::draw() {
    ofMaterial::begin();
    ofPlanePrimitive::draw();
    ofMaterial::end();
}

void    Particle::windowResized() {
    setPosition(rand() % MidiSettings::getWindowWidth(), rand() % MidiSettings::getWindowHeight(), 0);
        
    const float size = MidiSettings::getWindowWidth() * MidiSettings::getWindowHeight() * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}
