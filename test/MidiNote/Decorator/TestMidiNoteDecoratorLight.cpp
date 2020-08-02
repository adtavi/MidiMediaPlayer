//
//  TestMidiNoteDecoratorLight.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiNoteDecoratorLight.hpp"
#include "MidiNote.hpp"

class TestMidiNoteDecoratorLight
{
    unique_ptr<MidiNoteDecoratorLight> _decorator_light;
    
public:
    TestMidiNoteDecoratorLight() {
        MidiSettings::set_window(1024, 768);
        _decorator_light = make_unique<MidiNoteDecoratorLight>(new MidiNote(22, 100));
    };
    
    ofColor get_color() {
        return _decorator_light.get()->_color;
    }
    
    void set_position(const glm::vec3 & position) {
        _decorator_light.get()->setPosition(position);
    }
    
    bool to_delete() {
        return _decorator_light.get()->to_delete();
    }
    
    void set_off() {
        _decorator_light.get()->set_off();
    }
    
    glm::vec3 get_position() {
        return _decorator_light.get()->getPosition();
    }
    
    int get_pitch() {
        return _decorator_light.get()->get_pitch();
    }
    
    int get_velocity() {
        return _decorator_light.get()->get_velocity();
    }
    
    float get_max_y() {
        return _decorator_light.get()->_max_y;
    }
    
    bool is_on() {
        return _decorator_light.get()->_midi_note->is_on();
    }
    
    void new_press(int velocity) {
        return _decorator_light.get()->new_press(velocity);
    }
    
    void window_resized() {
        return _decorator_light.get()->window_resized();
    }
    
    void update() {
        return _decorator_light.get()->update();
    }
    
    float get_boom_rate() {
        return _decorator_light.get()->_boom_rate;
    }
    
    float get_max_angle() {
        return _decorator_light.get()->_max_angle;
    }
    
    float get_min_angle() {
        return _decorator_light.get()->_min_angle;
    }
    
    float get_angle_rate() {
        return _decorator_light.get()->_angle_rate;
    }
    
    float get_spotlight() {
        return _decorator_light.get()->getSpotlightCutOff();
    }
};

TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight", "[MidiNoteDecoratorLight]" ) {
    REQUIRE(get_color() == ofColor::red);
    
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);

    REQUIRE(get_spotlight() == get_max_angle());
}


TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight::to_delete", "[MidiNoteDecoratorLight]" ) {
    REQUIRE_FALSE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight::set_off", "[MidiNoteDecoratorLight]" ) {
    set_off();
    REQUIRE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight::new_press", "[MidiNoteDecoratorLight]" ) {
    int velocity = 50;
    new_press(velocity);
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(velocity));
    REQUIRE(get_spotlight() == get_max_angle());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight::update", "[MidiNoteDecoratorLight]" ) {    
    glm::vec3 position = get_position();
    position.y = get_max_y();
    set_position(position);
    update();
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y);
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate());
    
    position.y = get_max_y() + get_boom_rate() * 2;
    set_position(position);
    update();
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == get_max_y() + get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate() * 2);
    
    position.y = get_max_y() - get_boom_rate() * 2;
    set_position(position);
    update();
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == get_max_y() - get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate() * 3);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLight, "MidiNoteDecoratorLight::window_resized", "[MidiNoteDecoratorLight]" ) {
    MidiSettings::set_window(500, 200);
    window_resized();
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);
}
