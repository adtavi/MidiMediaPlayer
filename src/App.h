#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "MidiContainer.hpp"

class App : public ofBaseApp, public ofxMidiListener {
    
    MidiContainer*          _midi_notes;
    ofxMidiIn               _midi_in;
    queue<ofxMidiMessage>   _midi_messages;
        
public:
    void                    setup();
    void                    update();
    void                    draw();
    void                    exit();
    void                    windowResized(int width, int height);
    void                    newMidiMessage(ofxMidiMessage& eventArgs);
    
};
