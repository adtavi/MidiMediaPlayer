//
//  MidiNoteParticle.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#include "MidiNoteParticle.hpp"

MidiNoteParticle::MidiNoteParticle() {
    // Material
    setAmbientColor(ofFloatColor::black);
    setDiffuseColor(ofFloatColor::gold);
    setSpecularColor(ofFloatColor::gold);
    setShininess(0);
}

void    MidiNoteParticle::init(int width, int height) {
    _window_width = width;
    _window_height = height;
    
    // Random velocity
    _velocity.x = ofRandom(-0.2, 0.2);
    _velocity.y = ofRandom(0, 0.6);
    _velocity.z = 0;
    
    // Initial random pos
    setPosition(rand() % _window_width, rand() % _window_height, 0);
    
    // Random orientation
    setOrientation(glm::vec3(rand() % 360, rand() % 360, rand() % 360));
    
    // Size
    const float size = _window_width * _window_height * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}

void    MidiNoteParticle::update() {
    // Update position
    setPosition(getPosition() + _velocity);
    
    // If it went out of screen, move it upwards
    if (getY() + _velocity.y > _window_height) {
        setPosition(getX(), 0, getZ());
    }
    
    // Check if it goes out of bound for width
    if (getX() > _window_width) {
        setPosition(_window_width, getY(), getZ());
        _velocity.x *= -1.0;
    } else if (getX() < 0) {
        setPosition(0, getY(), getZ());
        _velocity.x *= -1.0;
    }
}

void    MidiNoteParticle::draw() {
    ofMaterial::begin();
    ofPlanePrimitive::draw();
    ofMaterial::end();
}

void    MidiNoteParticle::windowResized(int width, int height) {
    _window_width = width;
    _window_height = height;
    
    setPosition(rand() % _window_width, rand() % _window_height, 0);
        
    const float size = _window_width * _window_height * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}
