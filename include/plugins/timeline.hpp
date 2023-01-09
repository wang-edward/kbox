#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "allolib/include/al/io/al_AudioIO.hpp"
#include "track.hpp"
class timeline {
    public:
        static const int NUMBER_TRACKS = 1;
        long long current_position;
        track tracks[NUMBER_TRACKS];
        bool playing = true;

        void render(al::AudioIOData &io);
        void align_tracks();
        void init();
        

    private:
        void init_files();
        

};

#endif