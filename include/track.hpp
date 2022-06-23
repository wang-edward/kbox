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

        bool in_range (long long current_position);
        void set_position(long long new_position);
        float output();
        void align(long long current_position);
        void load_path(const char* _path);
    protected:
        long long start_position = 0; //TODO custom start position of sample
        long long end_position;
        gam::SamplePlayer<> player;
        float gain = 0.2;
};

#endif