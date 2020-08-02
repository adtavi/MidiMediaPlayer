//
//  TestMidiSettings.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiSettings.hpp"

TEST_CASE( "check_const", "[MidiSettings]") {
    REQUIRE( MidiSettings::get_num_keys() == 87);
    REQUIRE( MidiSettings::get_min_pitch() == 21);
    REQUIRE( MidiSettings::get_num_vel() == 100);
}

TEST_CASE( "set_window", "[MidiSettings]" ) {
    float my_epsilon = 0.001f;
    int window_width = 1200;
    int window_height = 750;
    
    MidiSettings::set_window(window_width, window_height);
    
    REQUIRE( MidiSettings::get_window_width() == window_width);
    REQUIRE( MidiSettings::get_window_height() == window_height);
    REQUIRE( MidiSettings::get_key_width() == Approx(static_cast<float>(window_width) / static_cast<float>(MidiSettings::get_num_keys())).epsilon(my_epsilon));
    REQUIRE( MidiSettings::get_velocity_height() == Approx(static_cast<float>(window_height) / static_cast<float>(MidiSettings::get_num_vel())).epsilon(my_epsilon));
}

TEST_CASE( "calc_y_by_velocity", "[MidiSettings]" ) {
    float my_epsilon = 0.001f;
    
    REQUIRE( MidiSettings::calc_y_by_velocity(MidiSettings::get_num_vel()) == Approx(0).epsilon(my_epsilon));
    REQUIRE( MidiSettings::calc_y_by_velocity(0) == Approx(MidiSettings::get_window_height()).epsilon(my_epsilon));
    REQUIRE( MidiSettings::calc_y_by_velocity(50) == Approx(static_cast<float>(MidiSettings::get_window_height())/static_cast<float>(2)).epsilon(my_epsilon));
}

TEST_CASE( "set_pedal", "[MidiSettings]" ) {
    REQUIRE_FALSE(MidiSettings::is_pedal());
    MidiSettings::set_pedal(true);
    REQUIRE( MidiSettings::is_pedal());
    MidiSettings::set_pedal(false);
    REQUIRE_FALSE(MidiSettings::is_pedal());
}
