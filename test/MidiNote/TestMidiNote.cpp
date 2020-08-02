//
//  TestMidiNote.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//

#include "catch.hpp"
#include "MidiNote.hpp"

TEST_CASE( "MidiNote", "[MidiNote]" ) {
    int pitch = 22;
    int velocity = 100;
    MidiNote midi_note(pitch, velocity);
    
    REQUIRE(midi_note.get_pitch() == pitch);
    REQUIRE(midi_note.get_velocity() == velocity);
    REQUIRE(midi_note.is_on());
}

TEST_CASE( "MidiNote::to_delete", "[MidiNote]" ) {
    int pitch = 22;
    int velocity = 100;
    MidiNote midi_note(pitch, velocity);
    
    REQUIRE_FALSE(midi_note.to_delete());
}

TEST_CASE( "is_on", "[MidiNote]" ) {
    int pitch = 22;
    int velocity = 100;
    MidiNote midi_note(pitch, velocity);
    
    REQUIRE(midi_note.is_on());
    midi_note.set_off();
    REQUIRE_FALSE(midi_note.is_on());
}

TEST_CASE( "new_press", "[MidiNote]" ) {
    int pitch = 22;
    int velocity = 100;
    MidiNote midi_note(pitch, velocity);
    midi_note.set_off();
    
    int new_velocity = 50;
    midi_note.new_press(new_velocity);
    REQUIRE(midi_note.get_velocity() == new_velocity);
}
