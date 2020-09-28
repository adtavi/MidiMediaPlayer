//
//  TimeContainer.hpp
//  MidiMediaPlayer
//
//  Created by Adriel Taboada on 04/08/2020.
//

#pragma once

#include <numeric>
#include "ofxMidiMessage.h"

using namespace std;

class TimeManager {
    friend class            TestTimeManager;
    
    static constexpr double _delta_note_min = 60;     // Minimum time for two key presses not to be considered simultaneous
    static constexpr double _delta_lower_threshold = 0.9;
    static constexpr double _delta_upper_threshold = 1.1;
    
    // Delta for midi notes
    vector<double>  _delta_notes;
    bool            _first_note;
    double          _delta_note;
    double          _delta_note_acc;
    unsigned short  _num_missmatched_notes;
    double          _half_note;
    
    // Delta for midi pedal
    vector<double>  _delta_pedals;
    bool            _first_pedal;
    double          _delta_pedal;
    double          _delta_pedal_acc;
    unsigned short  _num_missmatched_pedals;
    
    uint64_t        _elapsed_time;          // Time passed since launch
    uint64_t        _time_since_update;     // Time passed since last update
    
    void            process_delta_note(double delta);
    void            add_delta_note(double pedal);
    void            to_double_duration_notes();
    void            process_delta_pedal(double delta);

public:
    TimeManager();
    
    void             process_midi_message(const ofxMidiMessage & message);
    void             update_elapsed_time(uint64_t elapsed_time);
    uint64_t         get_delta_note() const;
    uint64_t         get_delta_pedal() const;
    uint64_t         get_time_since_update() const;
};
