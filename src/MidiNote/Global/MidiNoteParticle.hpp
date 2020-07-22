//
//  MidiNoteParticle.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#pragma once

#include "of3dPrimitives.h"
#include "ofMaterial.h"
#include <tuple>

class MidiNoteParticle: public ofPlanePrimitive, ofMaterial {
private:
    static constexpr float  _min_z = -100;
    static constexpr float  _max_z = 100;
    glm::vec3               _velocity;
    
public:
    MidiNoteParticle();
    
    void                    init();
    void                    update();
    void                    draw();
};
