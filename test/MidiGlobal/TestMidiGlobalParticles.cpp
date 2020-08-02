//
//  TestMidiGlobalParticles.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiGlobalParticles.hpp"

class TestMidiGlobalParticles
{
    unique_ptr<MidiGlobalParticles> _particles;
    
public:
    TestMidiGlobalParticles() {
        MidiSettings::set_window(1024, 768);
        _particles = make_unique<MidiGlobalParticles>();
    };
    
    unsigned int get_size() {
        return _particles.get()->_particles.size();
    }
    
    unsigned int get_num_particles() {
        return _particles.get()->_num_particles;
    }
    
    bool to_delete() {
        return _particles.get()->to_delete();
    }
};

TEST_CASE_METHOD(TestMidiGlobalParticles, "TestMidiGlobalParticles", "[MidiGlobalParticles]" ) {
    REQUIRE(get_size() == get_num_particles());
}

TEST_CASE_METHOD(TestMidiGlobalParticles, "toDelete", "[MidiGlobalParticles]") {
    REQUIRE_FALSE(to_delete());
}
