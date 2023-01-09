#ifndef WAV_EDITOR_HPP
#define WAV_EDITOR_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include "al/graphics/al_Graphics.hpp"
// #include "al/graphics/al_Font.hpp"
#include "al/io/al_AudioIO.hpp"
#include "Gamma/SamplePlayer.h"

class wav_editor  {
  public:

    void init();
    void init_path();
    void load_path(const char* _path);
    void init_mesh();
    void render(al::AudioIOData io);
    void render(al::Graphics& g);


  protected:
    long long current_position;
    long long start_cut;
    long long end_cut;
    gam::SamplePlayer<> player;
    al::Mesh wav;
    const char* path;
    const int resolution = 500;
    float h_zoom = 2;
};

#endif