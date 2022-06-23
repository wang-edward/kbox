#include "include/wav_editor.hpp"

void wav_editor:: init() {
    init_path();
    init_mesh();
}

void wav_editor:: init_path() {
    // std::string path = "./data/samples";
    // int i=0;
    // for (const auto& file : std::filesystem::directory_iterator(path)) {
    // // for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
    //     std::string s = file.path();
    //     load_path(s.c_str()); //convert string to const char*
    //     std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
    //     break; //TODO only run once
    // }
}

void wav_editor:: load_path(const char* _path) {
    path = _path;
    player.load(path);
    player.pos(player.frames());
}

void wav_editor::init_mesh () {
    wav.primitive(al::Mesh::LINE_STRIP);
    if (player.frames()>0) {
        //TODO check if long double overflow
        for (long double i=0;i<player.frames();i+=player.frames()/resolution) {
            player.pos(i);
            wav.vertex(i/player.frames()*h_zoom, player(), 0);
            std::cout<<i/player.frames()<<std::endl;
        }
        std::cout<<"total: "<<player.frames()<<std::endl;
    } else {
        std::cout<<"\nWAV_EDITOR DIDN'T LOAD SAMPLE (\"should segfault\")\n"<<std::endl;
    }
    
}

void wav_editor::render(al::Graphics& g) {
    g.color(1,1,1);
    g.draw(wav);
}

//TODO can you cout a const char*