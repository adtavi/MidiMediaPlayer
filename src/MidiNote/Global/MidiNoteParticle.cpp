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
    setSpecularColor(ofFloatColor::red);
    setShininess(24);
    
    // Size
    setWidth(2.0);
    setHeight(2.0);
}

void    MidiNoteParticle::init() {
    // Random velocity
    _vel.x = ofRandom(-0.2, 0.2);
    _vel.y = ofRandom(0, 0.6);
    _vel.z = ofRandom(-0.2, 0.2);
    
    // Initial random pos
    setPosition(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0);
    
    // Random orientation
    setOrientation(glm::vec3(ofRandom(0, 360), ofRandom(0, 360), ofRandom(0, 360)));
}

void    MidiNoteParticle::update() {
    // Update position
    setPosition(getPosition() + _vel);
    
    // If it went out of screen, move it upwards
    if (getY() + _vel.y > ofGetHeight()) {
        setPosition(getX(), 0, getZ());
    }
    
    // Check if it goes out of bound for width
    if (getX() > ofGetWidth()) {
        setPosition(ofGetWidth(), getY(), getZ());
        _vel.x *= -1.0;
    } else if (getX() < 0) {
        setPosition(0, getY(), getZ());
        _vel.x *= -1.0;
    }
}

void    MidiNoteParticle::draw() {
    ofMaterial::begin();
    ofPlanePrimitive::draw();
    ofMaterial::end();
}
