#include "include/timeline.hpp"
#include <time.h> // debug
#include <chrono>
#include <cmath>
#include <cstdint>
#include <algorithm>

using namespace std::chrono;

timeline:: timeline() {
    current_position = 0;

    // TODO get rid of DS_Store
    std::string path = "./data/beat";
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
            std::cout<<s.substr(2,s.length())<<std::endl;
            // std::cout<< s.substr(2,s.length())<<data[i].start_position<<data[i].end_position<<std::endl; //skip "./" in file path
            i++;
        }
    }

    for (auto& t : data) {
        t.rect.colors().clear();
        float h = std::rand()/(float)(RAND_MAX);
        al::Color temp = al::HSV(h,1,1.0);
        // al::Color temp = al::RGB(0,0,0);
        for (int i=0;i<6;i++) {
            t.rect.color(temp);
        }

        std::cout<<t.path<<std::endl;
    }

    data[0].set_position(452000);
    data[1].set_position(815000 - 452000 + 815000);
    data[1].gain = 0.06;
    data[2].set_position(815000);
    data[2].gain = 0.1;

    addRect(cursor, 0,-1, 0.01, 2);
    for (int i=0;i<6;i++) {
        cursor.color(al::RGB(1,1,1));
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
        t.render(g);
    }
    g.draw(cursor);
}

void timeline:: align_tracks() {
    for (int i=0;i<NUMBER_TRACKS;i++) {
        data[i].align(current_position);
    }
}

void timeline:: update_graphics() {
    //width of window

    left_side = current_position - step;
    right_side = current_position + step;

    long long timeline_frames = right_side - left_side;

    for (int i=0;i<NUMBER_TRACKS;i++) {
        track& t = data[i];
        // std::cout<<"track path: "<<t.path<<std::endl;

        long long l_frames, r_frames;
        if (t.get_start() - left_side < 0) {
            l_frames = 0;
        } else {
            l_frames = t.get_start() - left_side;
        }
        if (right_side - t.get_end() > 0) {
            r_frames = 0;
        } else {
            r_frames = right_side - t.get_end();
        }

        l_frames = std::max((long long)0, t.get_start() - left_side); //distance from left edge in frames
        r_frames = std::max((long long)0, right_side - t.get_end()); //distance from right edge in frames
        
        //width of track within window
        long long rect_frames = timeline_frames - l_frames - r_frames;

        //distance from left edge in units
        float l_dist = (float)l_frames / (float)timeline_frames;
        //distance from right edge in units
        float r_dist = (float)r_frames / (float)timeline_frames;

        //width of rectangle in units
        float rect_width = 2 * (float)rect_frames / (float)timeline_frames;

        float rect_position  = (float)r_dist - (float)l_dist;
        t.scale(rect_width, rect_position);
        // std::cout<<"l_frames: "<<l_frames<<" r_frames: "<<r_frames<<" timeline_frames: "<<timeline_frames<<" rect_frames: "<<rect_frames<<std::endl;
        // std::cout<<rect_width<<std::endl;
        t.rect.translate(rect_width/2 - 1, i * 0.5 - 1, 0);
    }

}
