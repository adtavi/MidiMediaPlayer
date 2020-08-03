//
//  MidiGlobalParticle.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include "MidiSettings.hpp"

class MidiGlobalParticle: private ofPlanePrimitive, ofMaterial {
    friend class TestMidiGlobalParticle;
    
    static constexpr float  _window_to_size_ratio = 0.0000026;
    
    glm::vec3               _velocity;
    
public:
    MidiGlobalParticle();
    
    void                    init();
    void                    update();
    void                    draw();
    void                    window_resized();
};
