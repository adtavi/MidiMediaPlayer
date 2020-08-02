//
//  TestMidiContainer.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiContainer.hpp"

class TestMidiContainer
{
    unique_ptr<MidiContainer> _midi_container;
    
public:
    TestMidiContainer() {
        MidiSettings::set_window(1024, 768);
        _midi_container = make_unique<MidiContainer>(1024, 768);
    };
    
    void process_midi_message(ofxMidiMessage & message) {
        _midi_container.get()->process_midi_message(message);
    }
    
    int get_num_global() {
        return _midi_container.get()->_midi_note_global.size();
    }
    
    int get_num_notes() {
        return _midi_container.get()->_midi_notes.size();
    }
    
    void window_resized(int width, int height) {
        _midi_container.get()->window_resized(width, height);
    }
    
    void update() {
        _midi_container.get()->update();
    }
};

TEST_CASE_METHOD(TestMidiContainer, "MidiContainer", "[MidiContainer]" ) {
    REQUIRE(get_num_global() == 2);
    REQUIRE(get_num_notes() == 0);
}

TEST_CASE_METHOD(TestMidiContainer, "process_midi_note_on", "[MidiContainer]") {
    REQUIRE(get_num_global() == 2);
    REQUIRE(get_num_notes() == 0);
    
    ofxMidiMessage message;
    message.status = MidiStatus::MIDI_NOTE_ON;
    message.pitch = 21;
    message.velocity = 100;
    process_midi_message(message);
    REQUIRE(get_num_notes() == 1);
    
    process_midi_message(message);
    REQUIRE(get_num_notes() == 1);
}

TEST_CASE_METHOD(TestMidiContainer,"process_midi_note_off", "[MidiContainer]" ) {
    ofxMidiMessage message;
    message.status = MidiStatus::MIDI_NOTE_OFF;
    message.pitch = 21;
    message.velocity = 100;
    process_midi_message(message);
    REQUIRE(get_num_notes() == 0);
    
    message.status = MidiStatus::MIDI_NOTE_ON;
    process_midi_message(message);
    REQUIRE(get_num_notes() == 1);
    
    message.pitch = 22;
    message.status = MidiStatus::MIDI_NOTE_OFF;
    process_midi_message(message);
    REQUIRE(get_num_notes() == 1);
    
    message.pitch = 21;
    message.status = MidiStatus::MIDI_NOTE_OFF;
    process_midi_message(message);
    REQUIRE(get_num_notes() == 1);
    
    update();
    REQUIRE(get_num_notes() == 0);
}

TEST_CASE_METHOD(TestMidiContainer, "process_midi_control_change", "[MidiContainer]" ) {
    REQUIRE_FALSE(MidiSettings::is_pedal());
    
    ofxMidiMessage message;
    message.status = MidiStatus::MIDI_CONTROL_CHANGE;
    message.control = 64;
    message.value = 127;
    process_midi_message(message);
    REQUIRE(MidiSettings::is_pedal());
    
    message.value = 5;
    process_midi_message(message);
    REQUIRE(MidiSettings::is_pedal());
    
    message.value = 0;
    process_midi_message(message);
    REQUIRE_FALSE(MidiSettings::is_pedal());
}

TEST_CASE_METHOD(TestMidiContainer,"TestMidiContainer::window_resized", "[MidiContainer]" ) {
    window_resized(600,300);
    REQUIRE(MidiSettings::get_window_width() == 600);
    REQUIRE(MidiSettings::get_window_height() == 300);
}
