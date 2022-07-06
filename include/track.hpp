#ifndef TRACK_HPP
#define TRACK_HPP

#include "Gamma/SamplePlayer.h"

class track {
    public:
        static constexpr float DEFAULT_GAIN = 0.2;
        track();
        track(const char* _path, float _gain);
        track (const track &obj);
        float output();
    //private:
        gam::SamplePlayer<> player;
        float gain = 0.2;
};

#endif
