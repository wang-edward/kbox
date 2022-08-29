#ifndef TRACK_HPP
#define TRACK_HPP

#include <string>
#include <filesystem>
#include "Gamma/SamplePlayer.h"
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/io/al_AudioIO.hpp"

class track {
    public:

        static constexpr float DEFAULT_GAIN = 0.2;
        al::Mesh rect;

        track(int _index);
        track(const char* _path, int _index);

        bool in_range (long long current_position);
        void set_position(long long new_position);
        void align(long long current_position);
        void load_path(const char* _path);
        void calculate_positions();
        float output();
        void render(al::Graphics& g);
        void scale(float width, float position);

        long long get_start();
        long long get_end();
        
    protected:
        long long start_position = 0; //TODO custom start position of sample
        long long end_position;
        gam::SamplePlayer<> player;
        float gain = DEFAULT_GAIN;
        int index;
        const float height = 1;
};

#endif
