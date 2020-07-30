#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "MidiNoteContainer.hpp"

class ofApp : public ofBaseApp, public ofxMidiListener {
    
    MidiNoteContainer*          _midi_notes;
    ofxMidiIn                   _midi_in;
    std::queue<ofxMidiMessage>  _midi_messages;
    
    // Deltas and time for onset detection
    uint64_t                    _delta;
    uint64_t                    _delta_acc;
    uint64_t                    _elapsed_update;
    uint64_t                    _elapsed_time;
        
public:
    void                        setup();
    void                        update();
    void                        draw();
    void                        exit();
    void                        windowResized(int width, int height);
    void                        newMidiMessage(ofxMidiMessage& eventArgs);
    
};
