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

#include "al/app/al_App.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"

#include "include/Sample.hpp"

#define AUDIO_BLOCK_SIZE 128

enum PLUGIN {PLUGIN_SAMPLER, PLUGIN_SUBTRACTIVE, PLUGIN_WAV_EDITOR};

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public al::App {
  
  box::Sample mySample{"data/samples/test/beat.wav", 0.4};

  void onInit() override {
    //TODO better config
    dimensions(960,640);
    fullScreen(true);
  }
  void onCreate() override { //TODO cleanup
    std::cout<<"hi\n\n\nHI\n\n"<<std::endl;

  }
  
  void onSound(al::AudioIOData &io) override {
    mySample.onProcess(io);
  }

  void onAnimate (double dt) override {

  }

  void onDraw (al::Graphics &g) override {

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
  MyApp app;

  // Start audio
  app.configureAudio(44100., AUDIO_BLOCK_SIZE, 2, 0);

  // Set up sampling rate for Gamma objects
  gam::Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
