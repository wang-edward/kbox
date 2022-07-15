#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "allolib/include/al/io/al_AudioIO.hpp"
#include "include/track.hpp"
class timeline {
    public:
        static const int NUMBER_TRACKS = 4;
        long long current_position;
        std::deque<track> data;
        bool playing = true;

        void render(al::AudioIOData &io);
        void align_tracks();
        void init();

    private:
        void init_files();

};

#endif
