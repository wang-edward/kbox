#include "include/timeline.hpp"

#include <iostream>

void timeline::init() {
    std::string path = "./data/samples";
    int i=0;
    // for (const auto& file : std::filesystem::directory_iterator(path)) {
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=number_samples) {
            break;
        }
        std::string s = file.path();
        const char* c = s.c_str();
        data.push_back(track(c, track::DEFAULT_GAIN));
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
        i++;
    }
}
void timeline::render(al::AudioIOData &io) {
    while(io()){
        float s = 0;
        for (int i=0;i<number_samples;i++) {
            s += data[i].output();
            std::cout<<"position: "<<data[i].player.pos()<<"data: "<<s<<"tot_frames: "<<data[i].player.frames()<<std::endl;
        }
        io.out(0) = io.out(1) = s;
    }
}
