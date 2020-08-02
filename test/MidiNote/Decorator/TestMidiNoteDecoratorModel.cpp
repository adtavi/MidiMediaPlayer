//
//  TestMidiNoteDecoratorModel.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiNoteDecoratorModel.hpp"
#include "MidiNote.hpp"

class TestMidiNoteDecoratorModel
{
    unique_ptr<MidiNoteDecoratorModel> _decorator_model;
    
public:
    TestMidiNoteDecoratorModel() {
        MidiSettings::set_window(1024, 768);
        _decorator_model = make_unique<MidiNoteDecoratorModel>(new MidiNote(22, 100));
    };
    
    void set_position(const glm::vec3 & position) {
        _decorator_model.get()->setPosition(position.x, position.y, position.z);
    }
    
    bool to_delete() {
        return _decorator_model.get()->to_delete();
    }
    
    void set_off() {
        _decorator_model.get()->set_off();
    }
    
    glm::vec3 get_position() {
        return _decorator_model.get()->getPosition();
    }
    
    int get_pitch() {
        return _decorator_model.get()->get_pitch();
    }
    
    int get_velocity() {
        return _decorator_model.get()->get_velocity();
    }
    
    float get_max_y() {
        return _decorator_model.get()->_max_y;
    }
    
    bool is_on() {
        return _decorator_model.get()->_midi_note->is_on();
    }
    
    void new_press(int velocity) {
        return _decorator_model.get()->new_press(velocity);
    }
    
    void window_resized() {
        return _decorator_model.get()->window_resized();
    }
    
    void update() {
        return _decorator_model.get()->update();
    }
    
    float get_boom_rate() {
        return _decorator_model.get()->_boom_rate;
    }
    
    float get_angle_rate() {
        return _decorator_model.get()->_angle_rate;
    }
    
    float get_window_to_scale_ratio() {
        return _decorator_model.get()->_window_to_scale_ratio;
    }
    
    float get_scale_() {
        return _decorator_model.get()->get_scale();
    }
    
    ofPoint get_scale() {
        return _decorator_model.get()->getScale();
    }
    
    float get_angle() {
        return _decorator_model.get()->getRotationAngle(1);
    }
    
    void init() {
        return _decorator_model.get()->init();
    }
};

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "init", "[MidiNoteDecoratorModel]" ) {
    init();
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == MidiSettings::calc_y_by_velocity(get_velocity()));
    REQUIRE(get_position().z == 0);
    
    REQUIRE(get_scale().x == get_scale_());
    REQUIRE(get_scale().y == get_scale_());
    REQUIRE(get_scale().z == get_scale_());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "MidiNoteDecoratorModel::to_delete", "[MidiNoteDecoratorModel]" ) {
    REQUIRE_FALSE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "MidiNoteDecoratorModel::set_off", "[MidiNoteDecoratorModel]" ) {
    REQUIRE_FALSE(to_delete());
    set_off();
    REQUIRE(to_delete());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "MidiNoteDecoratorModel::new_press", "[MidiNoteDecoratorModel]" ) {
    int velocity = 50;
    new_press(velocity);
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(velocity));
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "MidiNoteDecoratorModel::update", "[MidiNoteDecoratorModel]" ) {

    glm::vec3 position = get_position();
    float angle = get_angle();
    position.y = get_max_y();
    set_position(position);
    update();
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == position.y);
    REQUIRE(get_position().z == 0);
    REQUIRE(get_angle() == get_angle_rate());
    
    position.y = get_max_y() + get_boom_rate() * 2;
    set_position(position);
    update();
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == get_max_y() + get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_angle() == get_angle_rate()*2);

    position.y = get_max_y() - get_boom_rate() * 2;
    set_position(position);
    update();
    REQUIRE(get_position().x == position.x);
    REQUIRE(get_position().y == get_max_y() - get_boom_rate());
    REQUIRE(get_position().z == 0);
    REQUIRE(get_angle() == get_angle_rate()*3);
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "MidiNoteDecoratorModel::window_resized", "[MidiNoteDecoratorLight]" ) {
    glm::vec3 position = get_position();
    MidiSettings::set_window(500, 250);
    window_resized();
    
    REQUIRE(get_max_y() == MidiSettings::calc_y_by_velocity(get_velocity()));
    
    REQUIRE(get_position().x == MidiSettings::calc_x_by_pitch(get_pitch()));
    REQUIRE(get_position().y == position.y);
    REQUIRE(get_position().z == position.z);

    REQUIRE(get_scale().x == get_scale_());
    REQUIRE(get_scale().y == get_scale_());
    REQUIRE(get_scale().z == get_scale_());
}

TEST_CASE_METHOD(TestMidiNoteDecoratorModel, "get_scale", "[MidiNoteDecoratorLight]" ) {
    REQUIRE(get_scale_() == get_window_to_scale_ratio() * MidiSettings::get_window_height() * MidiSettings::get_window_width());
}
