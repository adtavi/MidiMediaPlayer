//
//  DeltaContainer.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#pragma once

#include "ofxMidiMessage.h"

class TimeContainer {
    
private:
    static double           _delta;
    static double           _delta_acc;
    constexpr static double _delta_min = 60000;
    static bool             _first;
    
public:
    TimeContainer();
    
    static void             process_midi_message(MidiStatus status, double delta_time);
    uint64_t                get_delta();
};
