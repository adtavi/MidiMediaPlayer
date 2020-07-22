#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "MidiNoteContainer.hpp"

class ofApp : public ofBaseApp, public ofxMidiListener {
   
    MidiNoteContainer           _midi_notes;
    ofxMidiIn                   _midi_in;
    std::queue<ofxMidiMessage>  _midi_messages;
    ofLight                     _light;
    
    uint64_t                    _delta;
    uint64_t                    _delta_acc;
    uint64_t                    _elapsed_update;
    uint64_t                    _elapsed_time;
        
    void                        drawMidiNotes();

public:
    void                        setup();
    void                        update();
    void                        draw();
    void                        exit();
    
    void                        newMidiMessage(ofxMidiMessage& eventArgs);

};
