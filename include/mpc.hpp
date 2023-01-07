#pragma once
#include "include/plugin.hpp"
#include "sample.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/io/al_AudioIO.hpp"
#include "include/plot.hpp"
namespace box {
class Mpc : Plugin {

public:
  Mpc();
  Mpc(std::initializer_list<box::Sample>);

  int size() const;
  
  void onProcess(al::AudioIOData &io) override;
  void onProcess(al::Graphics& g) override;

private:

  std::vector<box::Sample> samples;
  void init();
  void init_font();
  void init_files();
  void color_discs();
  void position_discs();
  void render(plot& p);
  void render(al::AudioIOData &io);
  void key_down(int key);
  
};

}