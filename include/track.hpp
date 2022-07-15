#ifndef TRACK_HPP
#define TRACK_HPP

#include <string>
#include <filesystem>
#include "Gamma/SamplePlayer.h"
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/io/al_AudioIO.hpp"

class track {
    public:

        static constexpr float DEFAULT_GAIN = 0.2;

        track();
        track(const char* _path);

        bool in_range (long long current_position);
        void set_position(long long new_position);
        void align(long long current_position);
        void load_path(const char* _path);
        void calculate_positions();
        float output();
    //protected:
        long long start_position = 0; //TODO custom start position of sample
        long long end_position;
        gam::SamplePlayer<> player;
        float gain = DEFAULT_GAIN;
};

#endif
