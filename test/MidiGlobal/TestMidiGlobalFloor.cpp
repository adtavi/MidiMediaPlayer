//
//  TestMidiGlobalFloor.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiGlobalFloor.hpp"

class TestMidiGlobalFloor
{
    unique_ptr<MidiGlobalFloor> _floor;
    
public:
    TestMidiGlobalFloor() {
        MidiSettings::set_window(1024, 768);
        _floor = make_unique<MidiGlobalFloor>();
    };
    
    void midi_note_on() {
        _floor->midi_note_on();
    }
    
    void midi_note_off() {
        _floor->midi_note_off();
    }
    
    void midi_control_change() {
        _floor->midi_control_change();
    }
    
    bool to_delete() {
        _floor->to_delete();
    }
    
    void window_resized() {
        _floor->window_resized();
    }
    
    void update(uint64_t delta_pedal, uint64_t time_since_update) {
        _floor->update( delta_pedal, time_since_update);
    }
    
    glm::vec3 get_position() {
        return _floor->getPosition();
    }
    
    float get_width() {
        return _floor->getWidth();
    }
    
    float get_height() {
        return _floor->getHeight();
    }
    
    glm::vec3 get_orientation() {
        return _floor->getOrientationEulerDeg();
    }
};

TEST_CASE_METHOD(TestMidiGlobalFloor, "MidiGlobalFloor", "[MidiGlobalFloor]" ) {
    REQUIRE(get_width() == MidiSettings::get_window_width()*2);
    REQUIRE(get_height() == MidiSettings::get_window_depth()*2);

    REQUIRE(get_position().x == MidiSettings::get_window_width()/2);
    REQUIRE(get_position().y == MidiSettings::get_window_height());
    REQUIRE(get_position().z == -MidiSettings::get_window_depth());
    
    REQUIRE(get_orientation().x == 90);
    REQUIRE(get_orientation().y == 0);
    REQUIRE(get_orientation().z == 0);
}

