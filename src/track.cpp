#include "include/track.hpp"

track::track(int _index) {
    index = _index;
    int x = 0.5 - (0.5 * index);
    int wh = 1.0 - (0.5 * index);
    // al::addRect(rect, 0, 0,1,1);
    al::addRect(rect, -1, x,wh,wh);
}

track::track(const char* _path, int _index) {
    
    //TODO change to super/inheritance
    index = _index;
    int x = 0.5 - (0.5 * index);
    int wh = 1.0 - (0.5 * index);
    // al::addRect(rect, 0, 0,1,1);
    al::addRect(rect, -1, x,wh,wh);

    load_path(_path);
    al::addRect(rect, 0, 0,1,1);
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

void calculate_positions() {

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
    rect.scale(width,1,1);
    // rect.translate(rand() / (float) RAND_MAX - 0.5, 0, 0);
}

long long track:: get_start() { return start_position; }

long long track::get_end() { return end_position; }
