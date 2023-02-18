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

#include "include/plugins/Sample.hpp"

#define AUDIO_BLOCK_SIZE 128

enum PLUGIN {PLUGIN_SAMPLER, PLUGIN_SUBTRACTIVE, PLUGIN_WAV_EDITOR};

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public al::App {
  
  box::Sample mySample{"data/samples/test/beat.wav", 0.4};
  al::Mesh square;
  al::Mesh mesh;
  al::Mesh circle;

  void onInit() override {
    //TODO better config
    dimensions(960,640);
    fullScreen(true);
  }
  void onCreate() override { //TODO cleanup
    std::cout<<"hi\n\n\nHI\n\n"<<std::endl;
    // square.primitive(al::Mesh::TRIANGLE_STRIP);
    al::addCube(square, 1);
    al::addDisc(circle, 0.5, 40);
    // First, we add the vertex positions in a zig-zag pattern.
    mesh.vertex(-1, 1, 0);   // 0: top-left corner
    // mesh.vertex(-1, -1, 0);  // 1: bottom-left corner
    // mesh.vertex(1, 1, 0);    // 2: top-right corner
    // mesh.vertex(1, -1, 0);   // 3: bottom-right corner
    mesh.vertex(0,0,0);
    mesh.vertex(1,1,0);

    // Next, we add the vertex colors (in RGB color space), using the same
    // order as the positions above.
    mesh.color(1, 0, 0);  // 0: red
    mesh.color(0, 1, 0);  // 1: green
    mesh.color(0, 0, 1);  // 2: blue
    mesh.color(1, 1, 1);  // 3: white
    // nav().pos(0, 0, 4);
    
    circle.color(1, 0, 0);  // 0: red
    circle.color(0, 1, 0);  // 1: green

  }
  
  void onSound(al::AudioIOData &io) override {
    mySample.onProcess(io);
  }

  void onAnimate (double dt) override {

  }

  void onDraw (al::Graphics &g) override {
    g.camera(al::Viewpoint::UNIT_ORTHO_INCLUSIVE);
    g.meshColor();
    g.clear();
    // g.draw(square);
    g.draw(mesh);
    g.draw(circle);
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
