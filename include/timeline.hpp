#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "allolib/include/al/io/al_AudioIO.hpp"
#include "include/track.hpp"
#include <algorithm>
class timeline {
    public:
        static const int NUMBER_TRACKS = 4;
        long long current_position;
        std::deque<track> data;
        bool playing = true;

        void init();
        void render(al::AudioIOData& io);
        void render(al::Graphics& g);
        void align_tracks();
        void update_graphics();

    private:
        void init_files();
        long long max_width = 10000;
        long long left_side = 0; //left side of current window
        long long right_side = 10000; //right side of current window
        long long step = 1000;
        // horizontal and vertical zoom
};

#endif
