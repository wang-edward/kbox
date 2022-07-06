#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "allolib/include/al/io/al_AudioIOData.hpp"
#include "include/track.hpp"
#include <filesystem>
class timeline {
    public:
        //render(al::Audioio);
        void init();
        void render(al::AudioIOData &io);
    private:
        std::vector<track> data;
        int number_samples = 1;
};


#endif
