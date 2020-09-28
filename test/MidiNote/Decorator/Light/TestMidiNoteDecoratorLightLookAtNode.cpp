//
//  TestMidiNoteDecoratorLightLookAtNode.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#include "catch.hpp"
#include "MidiNoteDecoratorLightLookAtNode.hpp"
#include "MidiNote.hpp"

class TestMidiNoteDecoratorLightLookAtNode
{
    unique_ptr<MidiNoteDecoratorLightLookAtNode> _decorator_light;
    
public:
    ofNode * _node;
    
    TestMidiNoteDecoratorLightLookAtNode() {
        MidiSettings::set_window(1024, 768);
        _node = new ofNode();
        _decorator_light = make_unique<MidiNoteDecoratorLightLookAtNode>(new MidiNote(22, 100), _node);
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
    
    void update(uint64_t delta_note, uint64_t time_since_update) {
        return _decorator_light.get()->update(delta_note, time_since_update);
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
    
    glm::vec3 get_orientation() {
        return _decorator_light.get()->getOrientationEulerDeg();
    }
    
    void    set_position() {
        return _decorator_light.get()->set_position();
    }
    
    void look_at() {
        return _decorator_light.get()->look_at();
    }
};

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode", "[MidiNoteDecoratorLightLookAtNode]" ) {
    REQUIRE(get_color() == ofColor::red);
    
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);

    REQUIRE(get_spotlight() == get_max_angle());
}


TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::to_delete", "[MidiNoteDecoratorLightLookAtNode]" ) {
    REQUIRE_FALSE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::set_off", "[MidiNoteDecoratorLightLookAtNode]" ) {
    set_off();
    REQUIRE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::new_press", "[MidiNoteDecoratorLightLookAtNode]" ) {
    int velocity = 50;
    new_press(velocity);
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(velocity));
    REQUIRE(get_spotlight() == get_max_angle());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::update", "[MidiNoteDecoratorLightLookAtNode]" ) {
    glm::vec3 position = get_position();
    position.y = get_max_y();
    set_position(position);
    update(0, 0);
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y);
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate());
    
    position.y = get_max_y() + get_boom_rate() * 2;
    set_position(position);
    update(0,0);
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == get_max_y() + get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate() * 2);
    
    position.y = get_max_y() - get_boom_rate() * 2;
    set_position(position);
    update(0,0);
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == get_max_y() - get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_spotlight() == get_max_angle() - get_angle_rate() * 3);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::window_resized", "[MidiNoteDecoratorLightLookAtNode]" ){
    new_press(50);
    update(0, 0);
    auto position = get_position();
    MidiSettings::set_window(500, 200);
    window_resized();
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == position.y);
    REQUIRE(get_position().z == - 0);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::look_at", "[MidiNoteDecoratorLightLookAtNode]" ){
    _node->setPosition(get_position().x, -MidiSettings::get_window_height(), get_position().z);
    
    look_at();

    REQUIRE(get_orientation().x == -90.f);
    REQUIRE(get_orientation().y == 0);
    REQUIRE(get_orientation().z == 0);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorLightLookAtNode, "MidiNoteDecoratorLightLookAtNode::set_position", "[MidiNoteDecoratorLightLookAtNode]" ){
    set_position();
    
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);
}
