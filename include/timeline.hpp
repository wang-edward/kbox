#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "allolib/include/al/io/al_AudioIO.hpp"
#include "track.hpp"
#include <vector>
class timeline {
    public:
        bool playing = true;

        void render(al::AudioIOData &io);
        void align_tracks();
        void init();
        void toggle_play();
    private:
        static const int NUMBER_TRACKS = 1;
        long long current_position = 0;
        std::vector<track>tracks;
        void init_files();

};

#endif
