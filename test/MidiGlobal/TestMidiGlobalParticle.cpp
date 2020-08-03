//
//  TestMidiGlobalParticle.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiGlobalParticle.hpp"

class TestMidiGlobalParticle
{
    std::unique_ptr<MidiGlobalParticle> _particle;
    
public:
    TestMidiGlobalParticle() {
        MidiSettings::set_window(1024, 768);
        _particle = std::make_unique<MidiGlobalParticle>();
    };
    
    const glm::vec3 & get_velocity() {
        return _particle.get()->_velocity;
    }
    
    glm::vec3 get_position() {
        return _particle.get()->getPosition();
    }
    
    glm::vec3 get_orientation() {
        return _particle.get()->getOrientationEulerDeg();
    }
    
    float get_window_to_size_ratio() {
        return _particle.get()->_window_to_size_ratio;
    }
    
    float get_width() {
        return _particle.get()->getWidth();
    }
    
    float get_height() {
        return _particle.get()->getHeight();
    }
    
    void init() {
        _particle.get()->init();
    }
    
    void update() {
        _particle.get()->update();
    }
    
    void set_position(glm::vec3 & position) {
        _particle.get()->setPosition(position);
    }
    
    void set_velocity(glm::vec3 & velocity) {
        _particle.get()->_velocity = velocity;
    }
    
    void window_resized() {
        _particle.get()->window_resized();
    }
};

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::init", "[MidiGlobalParticle]" ) {    
    init();
    
    REQUIRE((get_velocity().x >= -0.2 && get_velocity().x <= 0.2));
    REQUIRE((get_velocity().y >= 0 && get_velocity().y <= 0.6));
    REQUIRE(get_velocity().z == 0);
    
    REQUIRE((get_position().x >= 0 && get_position().x <= MidiSettings::get_window_width()));
    REQUIRE((get_position().y >= 0 && get_position().y <= MidiSettings::get_window_height()));
    REQUIRE((get_position().z >= -MidiSettings::get_window_height() && get_position().z <= 0));

    REQUIRE((get_orientation().x > -180 && get_orientation().x <= 180));
    REQUIRE((get_orientation().y > -180 && get_orientation().y <= 180));
    REQUIRE((get_orientation().z > -180 && get_orientation().z <= 180));
    
    const float size = MidiSettings::get_window_width() * MidiSettings::get_window_height() * get_window_to_size_ratio();
    REQUIRE(get_width() == size);
    REQUIRE(get_height() == size);
}

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::update", "[MidiGlobalParticle]" ) {
    init();
    
    glm::vec3 position = get_position();
    glm::vec3 velocity = get_velocity();
    
    update();
    
    REQUIRE(position.x + velocity.x == get_position().x);
    REQUIRE(position.y + velocity.y == get_position().y);
    REQUIRE(position.z + velocity.z == get_position().z);
}

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::update_x_min", "[MidiGlobalParticle]" ) {
    float velocity = -0.2;
    
    glm::vec3 position(-1, 0, 0);
    glm::vec3 velocity_vector(velocity, 0, 0);
    
    set_position(position);
    set_velocity(velocity_vector);
    
    update();
    
    REQUIRE(get_position().x == 0);
    REQUIRE(get_velocity().x == -velocity);
}

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::update_x_max", "[MidiGlobalParticle]" ) {
    float velocity = 0.2;
    
    glm::vec3 position(MidiSettings::get_window_width()+1, 0, 0);
    glm::vec3 velocity_vector(velocity, 0, 0);
    
    set_position(position);
    set_velocity(velocity_vector);
    
    update();
    
    REQUIRE(get_position().x == MidiSettings::get_window_width());
    REQUIRE(get_velocity().x == -velocity);
}

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::update_y_max", "[MidiGlobalParticle]" ) {
    float velocity = 0.2;
    
    glm::vec3 position(0, MidiSettings::get_window_height(), 0);
    glm::vec3 velocity_vector(0, velocity, 0);
    
    set_position(position);
    set_velocity(velocity_vector);
    
    update();
    
    REQUIRE(get_position().y == 0);
    REQUIRE(get_velocity().y == velocity);
}

TEST_CASE_METHOD(TestMidiGlobalParticle, "TestMidiGlobalParticle::window_resized", "[MidiGlobalParticle]") {
    MidiSettings::set_window(2, 2);
    
    window_resized();
    
    REQUIRE(get_velocity().x == 0);
    REQUIRE(get_velocity().y == 0);
    REQUIRE(get_velocity().z == 0);
    
    REQUIRE((get_position().x >= 0 && get_position().x <= MidiSettings::get_window_width()));
    REQUIRE((get_position().y >= 0 && get_position().y <= MidiSettings::get_window_height()));
    REQUIRE((get_position().z >= -MidiSettings::get_window_height() && get_position().z <= 0));
    
    const float size = MidiSettings::get_window_width() * MidiSettings::get_window_height() * get_window_to_size_ratio();
    REQUIRE(get_width() == size);
    REQUIRE(get_height() == size);
}
