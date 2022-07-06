#include "include/track.hpp"

track::track() {
    std::cout<<"empty init"<<std::endl;
}
track::track(const char* _path, float _gain) {
    std::cout<<"before loadpath"<<std::endl;
    player.load(_path);
    std::cout<<"after loadpath"<<std::endl;
    gain = _gain;
}
track::track(const track &obj) {
   //this.gain = obj. 
}
float track::output() {
    //return player() * gain;
    float temp = player.read(0) * gain;
    player.advance();
    return temp;
}

