#include "include/plugins/sample.hpp"

namespace box {

// ----------------------------------------------------
// constructors
// ----------------------------------------------------
Sample:: Sample (const char* _path, float _gain) {
    load_path(_path);
    gain = _gain;
}

Sample:: Sample(Sample& s) { player.buffer(s.player); }

Sample& Sample:: operator=(Sample& s) { 
    player.buffer(s.player); 
    return *this;
}

Sample:: Sample(Sample&& s) { player.buffer(s.player); }

Sample& Sample:: operator=(Sample&& s) {
    player.buffer(s.player);
    return *this;
}

// ----------------------------------------------------
// parameter change 
// ----------------------------------------------------

void Sample:: update_gain(float _gain) {
    gain = _gain;
}

void Sample:: update_envelope(float a, float d, float s, float r) {
    // TODO
}

// ----------------------------------------------------
// overrides 
// ----------------------------------------------------

void Sample:: onProcess(al::AudioIOData& io) {
    while (io()) {
        float cur = player() * gain;
        io.out(0) += cur;
        io.out(1) += cur;
    }
}
void Sample:: onProcess(al::Graphics& g) {

}

void Sample:: onTriggerOn(al::Keyboard const &k) {
    player.reset();
    // reset_color();
}

void Sample:: onTriggerOff(al::Keyboard const &k) {

}

// ----------------------------------------------------
// utils (private)
// ----------------------------------------------------

void Sample:: load_path(const char* _path) {
    path = _path;
    player.load(path);
    player.pos(player.frames());
}

}
//copy constructor
// sample:: sample (const sample &m) {
//     path = m.path;
//     gain = m.gain;
//     load_path(path);
// }

// sample& sample:: operator=(const sample& new_sample) {

// }

// sample:: ~sample() {

// }



// void sample:: reset_color() {
//     float h = std::rand()/(float)(RAND_MAX);
//     float s = std::rand()/(float)(RAND_MAX);
//     float v = std::rand()/(float)(RAND_MAX);

//     al::Color temp = al::HSV(h,1.0,1.0);
//     disc.transform_color(temp);
// }

// void sample:: trigger_on() {

// }

// float sample:: output() {
//     return player() * gain;
// }

// void sample:: render (plot& p) {
//     disc.render(p);
// }

