#include "include/track.hpp"
#include "al/math/al_Vec.hpp"

track::track(int _index) {
    index = _index;
    int x = 0.5 - (0.5 * index);
    int wh = 1.0 - (0.5 * index);
    // al::addRect(rect, 0, 0,1,1);
    al::addRect(rect, -1, x,wh,wh);
}

track::track(const char* _path, int _index) {
    path = _path;
    
    //TODO change to super/inheritance
    index = _index;


    load_path(_path);
    al::addRect(rect, -1, 0,0.5,0.5);
}

bool track:: in_range(long long current_position) {
    if (current_position<end_position && current_position>start_position) {
        return true;
    }
    return false;
}

void track:: set_position(long long new_position) {
    start_position = new_position;
    end_position = new_position + player.frames();
}

void track:: align(long long current_position) {
    if (in_range(current_position)) {
        player.pos(current_position - start_position);
    }
}

void track:: calculate_positions() {
    end_position = player.frames() + start_position; // TODO custom end position of sample
}

float track:: output() {
    // return player() * gain; //TODO check if float gets rounded
    float s = player.read(0) * gain; //TODO check if float gets rounded
    // player.advance();
    return s;
}



void track:: load_path(const char* _path) {
    player.load(_path);
    // player.pos(player.frames());
    end_position = player.frames() + start_position; // TODO custom end position of sample
}

void track:: render(al::Graphics& g) {
    g.draw(rect);
}

void track:: scale(float width, float position) {
    al::Vec3f min(0), max(0);
    rect.getBounds(min,max);
    // std::cout<<"min: "<<min<<"max: "<<max<<std::endl;
    // min (x, y, z) holds bottom left of rect
    // max (x, y, z) holds top right of rect

    //iterate through every vertice in rect
    for (auto& point : rect.vertices()) {
        // if its the biggest stretch it all the way to the right
        if (point.x == max.x) {
            point.x = width/2;
        } else {
            // else stretch all the way to left
            point.x = -width/2;
        }

        // might be unnecessary
        // if its the biggest stretch it all the way to the top
        if (point.y == max.y) {
            point.y = 0.5 * height;
        } else {
            // if its the smallest stretch it all the way to the bottom
            point.y = 0;
        }
    }
}

long long track:: get_start() { return start_position; }

long long track::get_end() { return end_position; }
