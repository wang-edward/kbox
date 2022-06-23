#include "include/sample.hpp"

//default constructor
sample:: sample() {
    gain = 0.2;
    reset_color();
}

void sample:: init(const char* _path, float _gain) {
    load_path(_path);
    update_gain(_gain);
    player.pos(player.frames());
}
//constructor
sample:: sample (const char* _path, float _gain) {
    load_path(_path);
    gain = _gain;
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

void sample:: load_path(const char* _path) {
    path = _path;
    player.load(path);
    player.pos(player.frames());
}

void sample:: update_gain(float _gain) {
    gain = _gain;
}

void sample:: update_envelope(float a, float d, float s, float r) {
    
}

void sample:: reset_color() {
    float h = std::rand()/(float)(RAND_MAX);
    float s = std::rand()/(float)(RAND_MAX);
    float v = std::rand()/(float)(RAND_MAX);

    al::Color temp = al::HSV(h,1.0,1.0);
    disc.transform_color(temp);
}

void sample:: trigger_on() {
    player.reset();

    reset_color();
}

float sample:: output() {
    return player() * gain;
}

void sample:: render (plot& p) {
    disc.render(p);
}

// void sample::onProcess(AudioIOData& io) { cout<<"asd"; }

// void sample::onProcess(Graphics& g) { cout<<"asd"; }

// void sample::onTriggerOn() { cout<<"asd"; }

// void sample::onTriggerOff() { cout<<"asd"; }