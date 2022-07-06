#include "include/timeline.hpp"

void timeline:: init() {
    init_files();
    // align_tracks();
}

void timeline:: init_files() {
    // // TODO get rid of DS_Store
    std::string path = "./data/samples";
    int i=0;
    // // // for (const auto& file : std::filesystem::directory_iterator(path)) {
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=NUMBER_TRACKS) {
            break;
        }
        std::string s = file.path();
        track temp_track;
        temp_track.load_path(s.c_str());
        tracks.push_back(temp_track);
        tracks[i].load_path(s.c_str()); //convert string to const char*
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
    //     i++;
    }
}

void timeline:: render (al::AudioIOData &io) {
     if (playing == true) {
         while (io()) {
             float s = 0;

             for (int i=0;i<NUMBER_TRACKS;i++) {
                 // std::cout<<i<<" ";
                 if (tracks.at(i).in_range(current_position)) {
                     float a  = tracks[i].output();
                     tracks.at(i).align(current_position);
                     std::cout<<a<<" ";
                     s+=a;
                 }
             }
             io.out(0) = io.out(1) = s;
             current_position++;
         }
         // current_position+=io.framesPerBuffer();
         std::cout<<current_position<<"\n"<<std::endl;
     }
}
 void timeline:: align_tracks() {
     for (int i=0;i<NUMBER_TRACKS;i++) {
         tracks.at(i).align(current_position);
     }
}

