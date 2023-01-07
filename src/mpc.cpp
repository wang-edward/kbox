#include "include/mpc.hpp"
namespace box {

Mpc::Mpc(std::initializer_list<box::Sample> ls) : samples{ls} {

}

int Mpc::size() const {
    return samples.size();
}

}
void mpc:: init() {
    init_files();
    position_discs();
    // init_font();
    color_discs();
}

void mpc:: init_font() {
    font.load("data/font/Minecraft.ttf", 100, 512);
    font.alignCenter();

    font.write(text, "EHLELLELASDH", 0.2f);
}

void mpc:: init_files() {
    std::string path = "./data/samples";
    int i=0;
    // for (const auto& file : std::filesystem::directory_iterator(path)) {
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=NUMBER_SAMPLES) {
            break;
        }
        std::string s = file.path();
        // if (s.substr(s.length()-3, s.length()) != ("wav")) {
        //     // i--;
        //     std::cout<<s;
        // }
        samples[i].load_path(s.c_str()); //convert string to const char*
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
        i++;
    }
}

void mpc:: color_discs() {
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        samples[i].reset_color();
    }
}

void mpc:: position_discs() {
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        // samples[i].disc.translate(((i%4)-1.5)/2,(floor(i/4)-1)/2,0); //TODO MAY 17
        int x = i%4;
        int y = floor(i/4);
        
        samples[i].disc.transform_position(30 + 60*x, 20 + 40*y);
        samples[i].disc.transform_radius(15);
    }
}

void mpc:: render (plot& p) {
    for (sample x : samples) {
        x.render(p);
    }
}

void mpc:: render(al::AudioIOData &io) {
    while(io()){
        float s = 0;
        for (int i=0;i<NUMBER_SAMPLES;i++) {
            s += samples[i].output();
        }
        io.out(0) = io.out(1) = s;
    }
}

void mpc:: key_down(int key) {
    samples[key].trigger_on();
}

