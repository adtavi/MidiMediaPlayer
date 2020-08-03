//
//  MidiGlobalParticle.cpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#include "MidiGlobalParticle.hpp"

MidiGlobalParticle::MidiGlobalParticle() {
    // Material
    setAmbientColor(ofFloatColor::black);
    setDiffuseColor(ofFloatColor::gold);
    setSpecularColor(ofFloatColor::gold);
    setShininess(0);
}

void    MidiGlobalParticle::init() {
    // Random velocity
    _velocity.x = ofRandom(-0.2, 0.2);
    _velocity.y = ofRandom(0, 0.6);
    _velocity.z = 0;
    
    // Initial random pos
    setPosition(rand() % MidiSettings::get_window_width(), rand() % MidiSettings::get_window_height(), -1 * (rand() % MidiSettings::get_window_depth()));
    
    // Random orientation
    setOrientation(glm::vec3(rand() % 360, rand() % 360, rand() % 360));
    
    // Size
    const float size = MidiSettings::get_window_width() * MidiSettings::get_window_height() * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}

void    MidiGlobalParticle::update() {
    // Update position
    setPosition(getPosition() + _velocity);
    
    // If it went out of screen, move it upwards
    if (getY() + _velocity.y > MidiSettings::get_window_height()) {
        setPosition(getX(), 0, getZ());
    }
    
    // Check if it goes out of bound for width
    if (getX() > MidiSettings::get_window_width()) {
        setPosition(MidiSettings::get_window_width(), getY(), getZ());
        _velocity.x *= -1.0;
    } else if (getX() < 0) {
        setPosition(0, getY(), getZ());
        _velocity.x *= -1.0;
    }
}

void    MidiGlobalParticle::draw() {
    ofMaterial::begin();
    ofPlanePrimitive::draw();
    ofMaterial::end();
}

void    MidiGlobalParticle::window_resized() {
    setPosition(rand() % MidiSettings::get_window_width(), rand() % MidiSettings::get_window_height(), -1 * (rand() % MidiSettings::get_window_depth()));
    
    const float size = MidiSettings::get_window_width() * MidiSettings::get_window_height() * _window_to_size_ratio;
    setWidth(size);
    setHeight(size);
}
