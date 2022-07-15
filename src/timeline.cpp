#include "include/timeline.hpp"

void timeline:: init() {
    current_position = 0;
    init_files();
    // align_tracks();
}

void timeline:: init_files() {
    // TODO get rid of DS_Store
    std::string path = "./data/samples";
    int i=0;
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        bool flag = true;
        if (i>=NUMBER_TRACKS) {
            break;
        }
        std::string s = file.path();
        if (s.substr(s.length()-3, s.length())=="wav") {
            track temp_track(s.c_str());

            data.emplace_back(temp_track);

            std::cout<< s.substr(2,s.length())<<data[i].start_position<<data[i].end_position<<std::endl; //skip "./" in file path
            i++;

        }
    }
}

void timeline:: render (al::AudioIOData &io) {

    if (playing == true) {
        while (io()) {
            float s = 0;

            for (int i=0;i<NUMBER_TRACKS;i++) {
                // std::cout<<i<<" ";
                if (data[i].in_range(current_position)) {
                    float a  = data[i].output();
                    data[i].align(current_position);
                    //std::cout<<a<<" ";
                    s+=a;
                }
            }
            io.out(0) = io.out(1) = s;
            current_position++;
        }
        // current_position+=io.framesPerBuffer();
        //std::cout<<current_position<<"\n"<<std::endl;
    }
}

void timeline:: align_tracks() {
    for (int i=0;i<NUMBER_TRACKS;i++) {
        data[i].align(current_position);
    }
}
