#pragma once
#include "plugins/Plugin.hpp"
#include "plugins/Sample.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/io/al_AudioIO.hpp"
namespace box {
class Mpc : Plugin {

public:
  Mpc();
  Mpc(std::initializer_list<box::Sample>);

  int size() const;
  
  void onProcess(al::AudioIOData& io) override;
  void onProcess(al::Graphics& g) override;
  void onTriggerOn(al::Keyboard const &k) override;
  void onTriggerOff(al::Keyboard const &k) override;

private:
  static constexpr int MAX_SIZE = 16;
  std::vector<box::Sample> samples;
  
  void init_files();
  void color_discs();
  void position_discs();
  void key_down(int key);
  
};

}