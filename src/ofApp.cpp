#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // print input ports to console
    _midi_in.listInPorts();
    
    // open port by number (you may need to change this)
    _midi_in.openPort(0);
    //midiIn.openPort("IAC Pure Data In");    // by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    _midi_in.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    _midi_in.addListener(this);
    
    // print received messages to the console
    _midi_in.setVerbose(false);
    
    MidiNote::setPedal(false);
    MidiNoteSphere::setFrame(ofGetWidth(), ofGetHeight());
    
    _color.r = ofRandom( 0, 127 );
    _color.g = ofRandom( 0, 127 );
    _color.b = 255;
    
    ofFill();
    
    _delta_acc = 0.f;
    _right = false;
    _left = false;
    _light_step = 25;
    
    ofSetSmoothLighting(true);
    _light.setAmbientColor(ofFloatColor(.2f, .2f, .2f));
    _light.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    _light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    _light.setAttenuation(1.f, 0.f, 0.f);
    //_light.setSpotlight(90.f, 1.0);
    //_light.setDirectional();
    _light.setPosition(ofGetWidth()/2, ofGetHeight()/5, 0);
    _light.enable();
    
    //    void setDirectional();
    //
    //    void setSpotlight( float spotCutOff=45.f, float exponent=0.f );
    
    //    void setPointLight();
    
    //    void setAttenuation( float constant=1.f, float linear=0.f, float quadratic=0.f );
    
    //    void setAreaLight(float width, float height);
    
    //glm::vec3 lookat = _light.getLookAtDir();
    //cout << "[" << lookat.x << ";" << lookat.y << ";" << lookat.z << "]" << std::endl;
    
    ofEnableLighting();
}

//--------------------------------------------------------------
void ofApp::update(){
    _elapsed_update = (ofGetElapsedTimeMicros() - _elapsed_time);
    _elapsed_time = ofGetElapsedTimeMicros();

    updateColor();
    updateLightPosition();
    
    while (!_midi_messages.empty()) {
        auto message = _midi_messages.front();
        
        _delta_acc += message.deltatime;
        
        //cout << message.toString() << std::endl;
        if (message.status == MIDI_NOTE_ON) {
            _delta = _delta_acc * 1000;
            _delta_acc = 0;
            
            updateLightDirection();
            
            _midi_notes.processMidiNoteOn(message, _color);
        } else if (message.status == MIDI_NOTE_OFF) {
            _midi_notes.processMidiNoteOff(message);
        } else if (MIDI_CONTROL_CHANGE) {
            _midi_notes.processMidiControlChange(message);
        }
        else {
            cout << message.toString() << std::endl;
        }
        
        _midi_messages.pop();
    }
    
    _midi_notes.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    _light.draw();
    
    drawMidiNotes();
}

//--------------------------------------------------------------
void ofApp::exit() {
    // clean up
    _midi_notes.clear();
    _midi_in.closePort();
    _midi_in.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    // add the latest message to the message queue
    _midi_messages.push(msg);
}

void ofApp::drawMidiNotes() {
    
    for (auto & midi_note: _midi_notes) {
        if (midi_note->toDraw())
        {
            ofSetColor(midi_note->getColor());
            midi_note->draw();
        }
    }
}

void ofApp::updateColor() {
    _color.r = (_color.r + 1) % 127;
    _color.g = (_color.g + 1) % 127;
    // _color.b = (_color.b + 1) % 255;
}

void ofApp::updateLightDirection() {
    if (_delta > 20000) {   // In case we don't play notes at the same time
        _right = ! _right;
        _left = ! _right;
        
        glm::vec3 position = _light.getPosition();
        
        if (_right) {
            _light_step = (ofGetWidth() - position.x) / (_delta / _elapsed_update);
        } else {
            _light_step = position.x / (_delta / _elapsed_update);
        }
    }
}

void ofApp::updateLightPosition() {
    if (_right && _light.getX() + _light_step < ofGetWidth()) { // Going to the right
        _light.truck(_light_step);
    } else if (_left && _light.getX() - _light_step > 0) {      // Going to the left
        _light.truck(- _light_step);
    }
}
