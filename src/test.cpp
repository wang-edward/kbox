#include <iostream>
#include <vector>
#include <array>
#include <filesystem>
#include <string>
#include <random>

#include "Gamma/SamplePlayer.h"
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"
// #include <Player.h>

#include "al/app/al_App.hpp"
// #include "al/sound/al_SoundFile.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"
// #include "al/ui/al_FileSelector.hpp"

#include "include/track.hpp"
#include "include/timeline.hpp"


#define AUDIO_BLOCK_SIZE 128

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public al::App {

  timeline tl;

  void onInit() override {
    tl = timeline();
  }
  void onCreate() override {
    nav().pos(0,0,10);
    //data.push_back(gam::SamplePlayer<>("./data/samples/intro.wav"));
  }
  void onSound(al::AudioIOData &io) override {
    tl.render(io);
  }
  void onDraw (al::Graphics &g) override {
    g.clear();
    g.camera(al::Viewpoint::IDENTITY);
    g.meshColor();
    tl.update_graphics();
    tl.render(g);
  }
  bool onKeyDown(al::Keyboard const &k) override {
    return true;
  }
  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    return true;
  }
};

int main() {
    //data.push_back(player);

  MyApp app;
  app.configureAudio(44100., 256, 2, 0);
  gam::Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
