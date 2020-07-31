//
//  MidiNoteParticle.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include "MidiSettings.hpp"

namespace MidiGlobal {

class Particle: public ofPlanePrimitive, ofMaterial {
private:
    static constexpr float  _min_z = -100;
    static constexpr float  _max_z = 100;
    static constexpr float  _window_to_size_ratio = 0.0000026;
    
    glm::vec3               _velocity;
    
public:
    Particle();
    
    void                    init();
    void                    update();
    void                    draw();
    void                    windowResized();
};

}
