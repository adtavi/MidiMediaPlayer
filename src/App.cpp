#include "App.h"

//--------------------------------------------------------------
void App::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    ofSetLogLevel(OF_LOG_SILENT);
    
    _midi_in.listInPorts();                 // print input ports to console
    _midi_in.openPort(0);
    _midi_in.ignoreTypes(false, false, false); // don't ignore sysex, timing, & active sense messages,
    _midi_in.addListener(this);             // add ofApp as a listener
    _midi_in.setVerbose(false);             // don't print received messages to the console

    _midi_notes = new MidiContainer(ofGetWidth(), ofGetHeight());
        
    // Diffuse light
    ofFill();
    ofSetSmoothLighting(true);
    ofEnableDepthTest();
    ofEnableLighting();
}

//--------------------------------------------------------------
void App::update(){
    while (!_midi_messages.empty()) {
        auto message = _midi_messages.front();
        
        try {
            _midi_notes->process_midi_message(message);
        } catch (exception & ex) {
            cout << "Error: " << ex.what() << endl;
        }
        
        _midi_messages.pop();
    }
    
    _midi_notes->update(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void App::draw(){
    _midi_notes->draw();
}

//--------------------------------------------------------------
void App::exit() {
    // clean up
    _midi_in.closePort();
    _midi_in.removeListener(this);
    delete _midi_notes;
}

//--------------------------------------------------------------
void App::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    _midi_messages.push(msg);
}

void App::windowResized(int width, int height) {
    _midi_notes->window_resized(width, height);
}
