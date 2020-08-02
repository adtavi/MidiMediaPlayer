#include "App.h"

//--------------------------------------------------------------
void App::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    ofSetLogLevel(OF_LOG_SILENT);
    
    // print input ports to console
    _midi_in.listInPorts();
    
    // open port by number (you may need to change this)
    _midi_in.openPort(0);
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    _midi_in.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    _midi_in.addListener(this);
    
    // print received messages to the console
    _midi_in.setVerbose(false);
    
    _midi_notes = new MidiContainer(ofGetWidth(), ofGetHeight());
    
    // Note timing
    _delta = 0;
    _delta_acc = 0;
    _elapsed_update = 0;
    _elapsed_time = 0;
    
    // Diffuse light
    ofFill();
    ofSetSmoothLighting(true);
    ofEnableDepthTest();
    ofEnableLighting();
}

//--------------------------------------------------------------
void App::update(){
    _elapsed_update = (ofGetElapsedTimeMicros() - _elapsed_time);
    _elapsed_time = ofGetElapsedTimeMicros();
    
    MidiNoteDecoratorSphere::update_global();
    
    while (!_midi_messages.empty()) {
        auto message = _midi_messages.front();
        
        _delta_acc += message.deltatime;
        
        //_delta = _delta_acc * 1000;
        //_delta_acc = 0;
        
        try {
            _midi_notes->process_midi_message(message);
        } catch (exception & ex) {
            cout << "Error: " << ex.what() << endl;
        }
        
        _midi_messages.pop();
    }
    
    _midi_notes->update();
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
