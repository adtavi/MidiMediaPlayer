#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "MidiNotes.hpp"

class ofApp : public ofBaseApp, public ofxMidiListener {
   
    MidiNotes                   _midi_notes;
    ofColor                     _color;
    ofxMidiIn                   _midi_in;
    std::queue<ofxMidiMessage>  _midi_messages;
    ofLight                     _light;
    bool                        _right;
    bool                        _left;
    int                         _light_step;
    
    uint64_t                    _delta;
    uint64_t                    _delta_acc;
    uint64_t                    _elapsed_update;
    uint64_t                    _elapsed_time;
        
    void drawMidiNotes();

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void updateColor();
    void updateLightPosition();
    void updateLightDirection();

};
