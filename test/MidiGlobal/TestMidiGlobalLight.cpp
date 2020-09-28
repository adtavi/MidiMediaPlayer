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
    
    bool to_delete() {
        _light->to_delete();
    }
    
    void window_resized() {
        _light->window_resized();
    }
    
    void update(uint64_t delta_pedal, uint64_t time_since_update) {
        _light->update(delta_pedal, time_since_update);
    }
    
    float get_min_constant_attenuation(){
        return _light->_min_constant_attenuation;
    }
    
    float get_max_constant_attenuation(){
        return _light->_max_constant_attenuation;
    }
    
    float get_constant_attenuation() {
        return _light->getAttenuationConstant();
    }
    
    float get_min_linear_attenuation(){
        return _light->_min_linear_attenuation;
    }
    
    float get_max_linear_attenuation(){
        return _light->_max_linear_attenuation;
    }
    
    float get_linear_attenuation() {
        return _light->getAttenuationLinear();
    }
    
    float get_delta() {
        return _light->_delta;
    }
    
    float get_delta_acc() {
        return _light->_delta_acc;
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
    
    bool get_dimming() {
        return _light->_dimming;
    }
};

TEST_CASE_METHOD(TestMidiGlobalLight, "TestMidiGlobalLight", "[MidiGlobalLight]" ) {
    REQUIRE(get_min_constant_attenuation() == .5f);
    REQUIRE(get_max_constant_attenuation() == 1.f);

    
    REQUIRE(get_max_linear_attenuation() == 0.01f);
    REQUIRE(get_min_linear_attenuation() == 0.001f);

    REQUIRE(get_x() == MidiSettings::get_window_width()/static_cast<float>(2));
    REQUIRE(get_y() == 0);
    REQUIRE(get_z() == 0);
}

TEST_CASE_METHOD(TestMidiGlobalLight,"update", "[MidiGlobalLight]" ) {
    
    REQUIRE_FALSE(get_dimming());
    uint64_t delta_pedal = 7;
    uint64_t time_since_update = 2;
    update(delta_pedal, time_since_update);
    REQUIRE(get_delta() == delta_pedal);
    REQUIRE(get_delta_acc() == delta_pedal);
    REQUIRE(get_dimming());
    REQUIRE(get_constant_attenuation() == get_min_constant_attenuation());
    REQUIRE(get_linear_attenuation() == get_min_linear_attenuation());
    
    float delta_acc = delta_pedal - time_since_update;
    update(delta_pedal, time_since_update);
    REQUIRE(get_delta() == delta_pedal);
    REQUIRE(get_delta_acc() == delta_acc);
    REQUIRE(get_dimming());
    REQUIRE(get_constant_attenuation() == get_max_constant_attenuation() - (get_max_constant_attenuation() - get_min_constant_attenuation()) * delta_acc/delta_pedal);
    REQUIRE(Approx(get_linear_attenuation()).epsilon(.00001f) == get_max_linear_attenuation() - (get_max_linear_attenuation() - get_min_linear_attenuation()) * delta_acc/delta_pedal);
    
    delta_acc = delta_pedal - 2*time_since_update;
    update(delta_pedal, time_since_update);
    REQUIRE(get_delta() == delta_pedal);
    REQUIRE(get_delta_acc() == delta_acc);
    REQUIRE(get_dimming());
    REQUIRE(get_constant_attenuation() == get_max_constant_attenuation() - (get_max_constant_attenuation() - get_min_constant_attenuation()) * delta_acc/delta_pedal);
    REQUIRE(Approx(get_linear_attenuation()).epsilon(.00001f) == get_max_linear_attenuation() - (get_max_linear_attenuation() - get_min_linear_attenuation()) * delta_acc/delta_pedal);
    
    
    delta_acc = delta_pedal - 3*time_since_update;
    update(delta_pedal, time_since_update);
    REQUIRE(get_delta() == delta_pedal);
    REQUIRE(get_delta_acc() == delta_acc);
    REQUIRE(get_dimming());
    REQUIRE(get_constant_attenuation() == get_max_constant_attenuation() - (get_max_constant_attenuation() - get_min_constant_attenuation()) * delta_acc/delta_pedal);
    REQUIRE(get_linear_attenuation() == get_max_linear_attenuation() - (get_max_linear_attenuation() - get_min_linear_attenuation()) * delta_acc/delta_pedal);
    
    delta_acc = delta_pedal - (time_since_update - delta_acc);
    update(0, time_since_update);
    REQUIRE(get_delta() == 0);
    REQUIRE(get_delta_acc() == 0);
    REQUIRE_FALSE(get_dimming());
}

TEST_CASE_METHOD(TestMidiGlobalLight,"to_delete", "[MidiGlobalLight]" ) {
    REQUIRE_FALSE(to_delete());
}

TEST_CASE_METHOD(TestMidiGlobalLight,"TestMidiGlobalLight::window_resized", "[MidiGlobalLight]" ) {
    int width = 500;
    int height = 500;
    MidiSettings::set_window(width, height);
    window_resized();
    REQUIRE(get_x() == width/2);
    REQUIRE(get_y() == 0);
    REQUIRE(get_z() == 0);
}
