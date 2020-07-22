//
//  MidiNoteParticle.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 21/07/2020.
//

#pragma once

#include "MidiNoteDecorator.hpp"
#include <tuple>

class MidiNoteParticle: public ofPlanePrimitive, ofMaterial {
private:
    glm::vec3   _vel;
        
public:
    MidiNoteParticle();
      
    void        init();
    void        update();
    void        draw();
};
