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
        //if file is a wav
        if (s.substr(s.length()-3, s.length())=="wav") {
            track temp_track(s.c_str(), i);

            data.emplace_back(temp_track);

            //std::cout<< s.substr(2,s.length())<<data[i].start_position<<data[i].end_position<<std::endl; //skip "./" in file path
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

void timeline:: render (al::Graphics& g) {
    for (track t : data) {
        t.rect.colors().clear();
        float h = std::rand()/(float)(RAND_MAX);
        //al::Color temp = al::HSV(0.5,0.5,0.5);
        al::Color temp = al::RGB(0,0,1);
        for (int i=0;i<6;i++) {
            t.rect.color(temp);
        }
        t.render(g);
    }
}

void timeline:: align_tracks() {
    for (int i=0;i<NUMBER_TRACKS;i++) {
        data[i].align(current_position);
    }
}

void timeline:: update_graphics() {
    for (track t: data) {

        long long l_frames = std::max((long long)0, t.get_start() - left_side); //distance from left edge in frames
        long long r_frames = std::max((long long)0, right_side - t.get_end()); //distance from right edge in frames

        //width of window
        long long timeline_frames = right_side - left_side;
        //width of track within window
        long long rect_frames = timeline_frames - l_frames - r_frames;

        //distance from left edge in units
        float l_dist = (float)l_frames / (float)timeline_frames;
        //distance from right edge in units
        float r_dist = (float)r_frames / (float)timeline_frames;

        //width of rectangle in units
        float rect_width = (float)rect_frames / (float)timeline_frames;

        float rect_position  = (float)r_dist - (float)l_dist;
        t.scale(rect_width, rect_position);
        //t.translate(width/2, 0, 0);
    }
}
