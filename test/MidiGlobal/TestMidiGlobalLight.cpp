//
//  TestMidiGlobalLight.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiGlobalLight.hpp"

class TestMidiGlobalLight
{
    unique_ptr<MidiGlobalLight> _light;
    
public:
    TestMidiGlobalLight() {
        MidiSettings::set_window(1024, 768);
        _light = make_unique<MidiGlobalLight>();
    };
    
    void midi_note_on() {
        _light->midi_note_on();
    }
    
    void midi_note_off() {
        _light->midi_note_off();
    }
    
    void midi_control_change() {
        _light->midi_control_change();
    }
    
    bool to_delete() {
        _light->to_delete();
    }
    
    void window_resized() {
        _light->window_resized();
    }
    
    void update() {
        _light->update();
    }
    
    float get_constant_attenuation(){
        return _light->_constant_attenuation;
    }
    
    float get_min_constant_attenuation(){
        return _light->_min_constant_attenuation;
    }
    
    float get_max_constant_attenuation(){
        return _light->_max_constant_attenuation;
    }
    
    float get_constant_attenuation_rate() {
        return _light->_constant_attenuation_rate;
    }
    
    float get_linear_attenuation(){
        return _light->_linear_attenuation;
    }
    
    float get_min_linear_attenuation(){
        return _light->_min_linear_attenuation;
    }
    
    float get_max_linear_attenuation(){
        return _light->_max_linear_attenuation;
    }
    
    float get_linear_attenuation_rate() {
        return _light->_linear_attenuation_rate;
    }
    int get_num_keys() {
        return _light->_num_keys;
    }
    
    float get_x() {
        return _light->getX();
    }
    
    float get_y() {
        return _light->getY();
    }
    
    float get_z() {
        return _light->getZ();
    }
};

TEST_CASE_METHOD(TestMidiGlobalLight, "TestMidiGlobalLight", "[MidiGlobalLight]" ) {
    REQUIRE(get_min_constant_attenuation() == .5f);
    REQUIRE(get_max_constant_attenuation() == 1.f);
    REQUIRE(get_constant_attenuation_rate() == (get_max_constant_attenuation() - get_min_constant_attenuation()) / 20);
    REQUIRE(get_constant_attenuation() == get_max_constant_attenuation());
    
    REQUIRE(get_max_linear_attenuation() == 0.01f);
    REQUIRE(get_min_linear_attenuation() == 0.001f);
    REQUIRE(get_linear_attenuation_rate() == (get_max_linear_attenuation() - get_min_linear_attenuation()) / 20);
    REQUIRE(get_linear_attenuation() == get_max_linear_attenuation());
    
    REQUIRE(get_x() == MidiSettings::get_window_width()/static_cast<float>(2));
    REQUIRE(get_y() == 0);
    REQUIRE(get_z() == -MidiSettings::get_window_depth()/static_cast<float>(2));

    REQUIRE(get_num_keys() == 0);
}

TEST_CASE_METHOD(TestMidiGlobalLight, "midi_note_on", "[MidiGlobalLight]") {
    midi_note_on();
    
    REQUIRE(get_constant_attenuation() == get_min_constant_attenuation());
    REQUIRE(get_linear_attenuation() == get_min_linear_attenuation());
    REQUIRE(get_num_keys() == 1);
    
    midi_note_on();
    REQUIRE(get_num_keys() == 2);
}

TEST_CASE_METHOD(TestMidiGlobalLight,"midi_note_off", "[MidiGlobalLight]" ) {
    midi_note_on();
    REQUIRE(get_num_keys() == 1);
    
    midi_note_off();
    REQUIRE(get_num_keys() == 0);
    
    midi_note_off();
    REQUIRE(get_num_keys() == 0);
}

TEST_CASE_METHOD(TestMidiGlobalLight,"update", "[MidiGlobalLight]" ) {
    REQUIRE(get_constant_attenuation() == get_max_constant_attenuation());
    REQUIRE(get_linear_attenuation() == get_max_linear_attenuation());
    
    midi_note_on();
    
    REQUIRE(get_constant_attenuation() == get_min_constant_attenuation());
    REQUIRE(get_linear_attenuation() == get_min_linear_attenuation());
    
    update();
    
    REQUIRE(get_constant_attenuation() == get_min_constant_attenuation() + get_constant_attenuation_rate());
    REQUIRE(get_linear_attenuation() == get_min_linear_attenuation() + get_linear_attenuation_rate());
}

TEST_CASE_METHOD(TestMidiGlobalLight,"to_delete", "[MidiGlobalLight]" ) {
    REQUIRE_FALSE(to_delete());
}

TEST_CASE_METHOD(TestMidiGlobalLight,"TestMidiGlobalLight::window_resized", "[MidiGlobalLight]" ) {
    int width = 500;
    int height = 500;
    MidiSettings::set_window(500, 500);
    window_resized();
    REQUIRE(get_x() == width/2);
    REQUIRE(get_y() == 0);
    REQUIRE(get_z() == -height/static_cast<float>(2));
}
