//
//  TestMidiNoteDecoratorSphere.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiNoteDecoratorSphere.hpp"
#include "MidiNote.hpp"

class TestMidiNoteDecoratorSphere
{
    unique_ptr<MidiNoteDecoratorSphere> _decorator_sphere;
    
public:
    TestMidiNoteDecoratorSphere() {
        MidiSettings::set_window(1024, 768);
        _decorator_sphere = make_unique<MidiNoteDecoratorSphere>(new MidiNote(22, 100));
    };
    
    ofColor get_base_color() {
        return _decorator_sphere.get()->_base_color;
    }
    
    ofColor get_color() {
        return _decorator_sphere.get()->_base_color;
    }
    
    void update_global() {
        _decorator_sphere.get()->update_global();
    }
    
    void set_position(const glm::vec3 & position) {
        _decorator_sphere.get()->setPosition(position);
    }
    
    bool to_delete() {
        return _decorator_sphere.get()->to_delete();
    }
    
    void set_off() {
        _decorator_sphere.get()->set_off();
    }
    
    glm::vec3 get_position() {
        return _decorator_sphere.get()->getPosition();
    }
    
    int get_pitch() {
        return _decorator_sphere.get()->get_pitch();
    }
    
    int get_velocity() {
        return _decorator_sphere.get()->get_velocity();
    }
    
    float get_min_y() {
        return _decorator_sphere.get()->_min_y;
    }
    
    bool get_decrease_y() {
        return _decorator_sphere.get()->_decrease_y;
    }
    
    float get_radius() {
        return _decorator_sphere.get()->getRadius();
    }
    
    bool is_on() {
        return _decorator_sphere.get()->_midi_note->is_on();
    }
    
    void new_press(int velocity) {
        return _decorator_sphere.get()->new_press(velocity);
    }
    
    void window_resized() {
        return _decorator_sphere.get()->window_resized();
    }
    
    void update() {
        return _decorator_sphere.get()->update();
    }
    
    float get_y_vel_slow() {
        return _decorator_sphere.get()->_y_vel_slow;
    }
    
    float get_y_vel_fast() {
        return _decorator_sphere.get()->_y_vel_fast;
    }
};

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere", "[MidiNoteDecoratorSphere]" ) {
    REQUIRE(get_base_color() == get_color());
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::get_window_height());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_decrease_y());
    REQUIRE(get_radius() == MidiNoteDecoratorSphere::calc_radius_by_velocity(get_velocity()));
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_global", "[MidiNoteDecoratorSphere]" ) {
    ofColor color = get_base_color();
    update_global();
    REQUIRE(get_base_color().r == color.r);
    REQUIRE(get_base_color().g == (color.g + 1) % 127);
    REQUIRE(get_base_color().b == 200 + (color.b - 199) % 55);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere::to_delete", "[MidiNoteDecoratorSphere]" ) {
    set_position(glm::vec3(0, MidiSettings::get_window_height() + 1, 0));
    REQUIRE_FALSE(to_delete());
    set_off();
    REQUIRE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "set_off", "[MidiNoteDecoratorSphere]" ) {
    REQUIRE(get_decrease_y());
    REQUIRE(is_on());
    set_off();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE_FALSE(is_on());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere::new_press", "[MidiNoteDecoratorSphere]" ) {
    set_position(glm::vec3(get_position().x, 0, get_position().z));
    int velocity = 50;
    new_press(velocity);
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_radius() == MidiNoteDecoratorSphere::calc_radius_by_velocity(get_velocity()));
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_decrease_y", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position = get_position();
    update();
    REQUIRE(get_decrease_y());
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y - get_y_vel_fast() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_min_y", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position = get_position();
    position.y = get_min_y();
    set_position(position);
    update();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y - get_y_vel_fast() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z);
}


TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_false_decrease_y", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position(get_position().x, get_min_y(), get_position().z);
    set_position(position);
    update();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y - get_y_vel_fast() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z);
    position = get_position();
    update();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y + get_y_vel_slow() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_slow", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position(get_position().x, get_min_y(), get_position().z);
    set_position(position);
    set_off();
    update();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y + get_y_vel_fast() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "window_resized", "[MidiNoteDecoratorSphere]" ) {
    MidiSettings::set_window(500, 250);
    window_resized();
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);
    REQUIRE(get_radius() == MidiNoteDecoratorSphere::calc_radius_by_velocity(get_velocity()));
}
