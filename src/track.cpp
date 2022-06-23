#include "include/track.hpp"

bool track:: in_range(long long current_position) {
    if (current_position<end_position && current_position>start_position) {
        return true;
    }
    return false;
}

float track:: output() {
    // return player() * gain; //TODO check if float gets rounded
    float s = player.read(0) * gain; //TODO check if float gets rounded
    // player.advance();
    return s;
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

void track:: load_path(const char* _path) {
    player.load(_path);
    // player.pos(player.frames());
    end_position = player.frames(); // TODO custom end position of sample
}