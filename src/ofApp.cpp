#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    
    MidiNote::setPedal(false);
    _midi_notes = new MidiNoteContainer(ofGetWidth(), ofGetHeight());
    
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
void ofApp::update(){
    _elapsed_update = (ofGetElapsedTimeMicros() - _elapsed_time);
    _elapsed_time = ofGetElapsedTimeMicros();
    
    MidiNoteSphere::updateGlobal();
    
    while (!_midi_messages.empty()) {
        auto message = _midi_messages.front();
        
        _delta_acc += message.deltatime;
        
        if (message.status == MIDI_NOTE_ON) {
            _delta = _delta_acc * 1000;
            _delta_acc = 0;
            
            _midi_notes->processMidiNoteOn(message);
        } else if (message.status == MIDI_NOTE_OFF) {
            _midi_notes->processMidiNoteOff(message);
        } else if (MIDI_CONTROL_CHANGE) {
            _midi_notes->processMidiControlChange(message);
        }
        else {
            cout << message.toString() << std::endl;
        }
        
        _midi_messages.pop();
    }
    
    _midi_notes->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    _midi_notes->draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    // clean up
    _midi_in.closePort();
    _midi_in.removeListener(this);
    delete _midi_notes;
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    _midi_messages.push(msg);
}

void ofApp::windowResized(int width, int height) {
    _midi_notes->windowResized(width, height);
}
