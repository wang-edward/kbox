#include "include/plugins/Mpc.hpp"
namespace box {

// ----------------------------------------------------
// constructors 
// ----------------------------------------------------

Mpc:: Mpc() { }

Mpc:: Mpc(std::initializer_list<box::Sample> ls) : samples{ls} { }

// ----------------------------------------------------
// public (utils)
// ----------------------------------------------------

int Mpc:: size() const {
    return samples.size();
}

// ----------------------------------------------------
// overrides 
// ----------------------------------------------------

void Mpc:: onProcess(al::AudioIOData& io) {
    for (auto sample : samples) {
        sample.onProcess(io);
    }
} 
void Mpc:: onProcess(al::Graphics& g) { }
void Mpc:: onTriggerOn(al::Keyboard const &k) {
    
}
void Mpc:: onTriggerOff(al::Keyboard const &k) override {

}

// ----------------------------------------------------
// private (utils) 
// ----------------------------------------------------

void Mpc:: initRandom() {
    std::string path = "/data/samples";
    int i=0;
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=MAX_SIZE) {
            break;
        }
        std::string s = file.path();
        // if (s.substr(s.length()-3, s.length()) != ("wav")) {
        //     // i--;
        //     std::cout<<s;
        // }
        samples.push_back({s.c_str()}); //convert string to const char*
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
        i++;
    }

}

} // namespace box

// void mpc:: color_discs() {
//     for (int i=0;i<NUMBER_SAMPLES;i++) {
//         samples[i].reset_color();
//     }
// }

// void mpc:: position_discs() {
//     for (int i=0;i<NUMBER_SAMPLES;i++) {
//         // samples[i].disc.translate(((i%4)-1.5)/2,(floor(i/4)-1)/2,0); //TODO MAY 17
//         int x = i%4;
//         int y = floor(i/4);
        
//         samples[i].disc.transform_position(30 + 60*x, 20 + 40*y);
//         samples[i].disc.transform_radius(15);
//     }
// }

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

