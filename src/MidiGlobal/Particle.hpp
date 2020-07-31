//
//  MidiNoteParticle.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"

namespace MidiGlobal {

class Particle: public ofPlanePrimitive, ofMaterial {
private:
    static constexpr float  _min_z = -100;
    static constexpr float  _max_z = 100;
    static constexpr float  _window_to_size_ratio = 0.0000026;
    
    glm::vec3               _velocity;
    int                     _window_width;
    int                     _window_height;
    
public:
    Particle();
    
    void                    init(int width, int height);
    void                    update();
    void                    draw();
    void                    windowResized(int width, int height);
};

}
