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
    
    void update_color() {
        _decorator_sphere.get()->update_color();
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
    
    float get_min_radius() {
        return _decorator_sphere.get()->_min_radius;
    }
    
    float get_max_radius() {
        return _decorator_sphere.get()->_max_radius;
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
    
    void update(uint64_t delta_note, uint64_t time_since_update) {
        return _decorator_sphere.get()->update(delta_note, time_since_update);
    }
    
    float get_vel_slow() {
        return _decorator_sphere.get()->_vel_slow;
    }
    
    float get_vel_fast() {
        return _decorator_sphere.get()->_vel_fast;
    }
    
    tuple<float,float>  calc_radius_by_velocity(int velocity) {
        return _decorator_sphere.get()->calc_radius_by_velocity(velocity);
    }
    
    uint64_t get_delta() {
        return _decorator_sphere.get()->_delta;
    }
    
    uint64_t get_delta_acc() {
        return _decorator_sphere.get()->_delta;
    }
    
    bool get_growing() {
        return _decorator_sphere.get()->_growing;
    }
    
    bool boom() {
        _decorator_sphere.get()->boom();
    }
    
    bool dolly() {
        _decorator_sphere.get()->dolly();
    }
};

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere", "[MidiNoteDecoratorSphere]" ) {
    REQUIRE(get_base_color() == get_color());
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::get_window_height());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_decrease_y());
    auto [min_radius, max_radius] = calc_radius_by_velocity(get_velocity());
    REQUIRE(get_radius() == min_radius);
    REQUIRE(get_delta() == 0);
    REQUIRE(get_delta_acc() == 0);
    REQUIRE_FALSE(get_growing());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "update_color", "[MidiNoteDecoratorSphere]" ) {
    ofColor color = get_base_color();
    update_color();
    REQUIRE(get_base_color().r == (color.r + 1) % 62);
    REQUIRE(get_base_color().g == (color.g + 1) % 127);
    REQUIRE(get_base_color().b == 200 + (color.b - 199) % 55);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere::to_delete", "[MidiNoteDecoratorSphere]" ) {
    REQUIRE_FALSE(to_delete());
    set_position(glm::vec3(0, MidiSettings::get_window_height() + 1, 0));
    REQUIRE(to_delete());
    set_position(glm::vec3(0, MidiSettings::get_window_height() + 1, MidiSettings::get_window_depth() + 1));
    REQUIRE(to_delete());
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
    auto [min_radius, max_radius] = calc_radius_by_velocity(get_velocity());
    set_position(glm::vec3(get_position().x, 0, get_position().z));
    int velocity = 50;
    new_press(velocity);
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_radius() == min_radius);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "MidiNoteDecoratorSphere::update", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position = get_position();
    update(0,0);
    REQUIRE(get_decrease_y());
    REQUIRE(get_position().y == position.y - get_vel_fast() * MidiSettings::get_velocity_height());
    REQUIRE(get_position().z == position.z - get_vel_fast());
    auto [min_radius, max_radius] = calc_radius_by_velocity(get_velocity());
    REQUIRE(get_radius() == min_radius);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "boom_decrease_y", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position = get_position();
    boom();
    REQUIRE(get_decrease_y());
    REQUIRE(get_position().y == position.y - get_vel_fast() * MidiSettings::get_velocity_height());
}


TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "boom_decrease_y_min_y", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position(get_position().x, get_min_y(), get_position().z);
    set_position(position);
    boom();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().y == get_min_y());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "boom_increasing_y_fast", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position(get_position().x, get_min_y(), get_position().z);
    set_position(position);
    set_off();
    REQUIRE_FALSE(get_decrease_y());
    boom();
    REQUIRE(get_position().y == position.y + get_vel_fast() * MidiSettings::get_velocity_height());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "boom_increasing_y_slow", "[MidiNoteDecoratorSphere]" ) {
    glm::vec3 position(get_position().x, get_min_y(), get_position().z);
    set_position(position);
    boom();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().y == get_min_y());
    boom();
    REQUIRE_FALSE(get_decrease_y());
    REQUIRE(get_position().y == position.y + get_vel_slow() * MidiSettings::get_velocity_height());
}


TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "dolly_slow", "[MidiNoteDecoratorSphere]" ) {
    auto position = get_position();
    set_off();
    dolly();
    REQUIRE(get_position().z == position.z - get_vel_slow());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "dolly_fast", "[MidiNoteDecoratorSphere]" ) {
    auto position = get_position();
    dolly();
    REQUIRE(get_position().z == position.z - get_vel_fast());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "set_radius", "[MidiNoteDecoratorSphere]" ) {
    
    REQUIRE_FALSE(get_growing());
    uint64_t delta_note = 7;
    uint64_t time_since_update = 2;
    update(delta_note, time_since_update);
    REQUIRE(get_delta() == delta_note);
    REQUIRE(get_delta_acc() == delta_note);
    REQUIRE(get_growing());
    REQUIRE(get_radius() == get_min_radius());
    
    float delta_acc = delta_note - time_since_update;
    update(delta_note, time_since_update);
    REQUIRE(get_delta() == delta_note);
    REQUIRE(get_delta_acc() == delta_note);
    REQUIRE(get_growing());
    REQUIRE(Approx(get_radius()) == get_min_radius() + (get_max_radius() - get_min_radius()) * delta_acc/delta_note);
    
    delta_acc = delta_note - 2*time_since_update;
    update(delta_note, time_since_update);
    REQUIRE(get_delta() == delta_note);
    REQUIRE(get_delta_acc() == delta_note);
    REQUIRE(get_growing());
    REQUIRE(get_radius() == get_min_radius() + (get_max_radius() - get_min_radius()) * delta_acc/delta_note);
    
    delta_acc = delta_note - 3*time_since_update;
    update(delta_note, time_since_update);
    REQUIRE(get_delta() == delta_note);
    REQUIRE(get_delta_acc() == delta_note);
    REQUIRE(get_growing());
    REQUIRE(get_radius() == get_min_radius() + (get_max_radius() - get_min_radius()) * delta_acc/delta_note);
    
    
    delta_acc = delta_note - (time_since_update - delta_acc);
    update(delta_note, time_since_update);
    REQUIRE(get_delta() == delta_note);
    REQUIRE(get_delta_acc() == delta_note);
    REQUIRE(get_growing());
    REQUIRE(get_radius() == get_min_radius() + (get_max_radius() - get_min_radius()) * delta_acc/delta_note);
    
    update(0, time_since_update);
    REQUIRE(get_delta() == 0);
    REQUIRE(get_delta_acc() == 0);
    REQUIRE_FALSE(get_growing());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "window_resized", "[MidiNoteDecoratorSphere]" ) {
    auto [min_radius, max_radius] = calc_radius_by_velocity(get_velocity());
    MidiSettings::set_window(500, 250);
    window_resized();
    REQUIRE(get_min_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);
    REQUIRE(get_radius() == min_radius);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorSphere, "calc_radius_by_velocity", "[MidiNoteDecoratorSphere]" ) {
    int velocity = 100;
    auto [min_radius, max_radius] = calc_radius_by_velocity(velocity);
    REQUIRE(min_radius == MidiSettings::get_key_width() + MidiSettings::get_key_width() * (velocity/100.));
    REQUIRE(max_radius == MidiSettings::get_key_width() + 2 * MidiSettings::get_key_width() * (velocity/100.));
}


