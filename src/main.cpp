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
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"


#define AUDIO_BLOCK_SIZE 128

enum PLUGIN {PLUGIN_SAMPLER, PLUGIN_SUBTRACTIVE, PLUGIN_WAV_EDITOR};

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

#include "include/sample.hpp"
#include "include/mpc.hpp"
#include "include/SineEnv.hpp"
#include "include/wav_editor.hpp"
#include "include/plot.hpp"
#include "include/circle.hpp"
#include "include/sprite.hpp"

#include "include/io/CAT9555.hpp"


struct MyApp : public al::App {
  PLUGIN CURRENT_PLUGIN = PLUGIN_SUBTRACTIVE;

  al::PolySynth pSynth;

  void onInit() override {
    //TODO better config
    dimensions(960,640);
  }
  void onCreate() override { //TODO cleanup
    // pSynth.allocatePolyphony<SineEnv>(16);
    // navControl().active(false);
    // nav().pos(0,0,10);
  }
  
  void onSound(al::AudioIOData &io) override {
    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):      // SAMPLER
          // std::cout<<"sampler is on"<<std::endl;
          // sampler.render(io);
        break;  
      case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
        pSynth.render(io);
        break;
    }
  }

  void onAnimate (double dt) override {

  }

  void onDraw (al::Graphics &g) override {
    g.camera(Viewpoint::IDENTITY);  
    g.clear();

    
    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):      // SAMPLER
        // sampler.render(screen);
        // sampler.color_discs();
        break;
      case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
        pSynth.render(g);
        break;
      case (PLUGIN_WAV_EDITOR):
        // editor.render(g);
        break;
    }
  }

  bool onKeyDown(al::Keyboard const &k) override {
    int key_pressed = al::asciiToIndex(k.key());
    std::cout<<key_pressed<<std::endl; // DEBUG

    swap_screens(key_pressed);

    switch (CURRENT_PLUGIN) {
      // case (PLUGIN_SAMPLER):      // SAMPLER
        
      //   if (key_pressed>=20 && key_pressed<mpc::NUMBER_SAMPLES +20) {
      //     key_pressed = key_pressed - 20;
      //     sampler.key_down(key_pressed);
      //   }
      //   break;
      case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
        int midiNote = al::asciiToMIDI(k.key());
        if (midiNote > 0) {
          float frequency = ::pow(2., (midiNote - 69.) / 12.) * 440.;
          SineEnv* voice = pSynth.getVoice<SineEnv>();
          std::cout<<frequency<<std::endl;
          voice->freq(frequency); 
          pSynth.triggerOn(voice, 0, midiNote);
        }

        break;
    }
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):
      // TODO: ADD SAMPLER KEYUP
      break;
      case (PLUGIN_SUBTRACTIVE):
        int midiNote = al::asciiToMIDI(k.key());
        if (midiNote > 0) pSynth.triggerOff(midiNote);
      break;
    }
    return true;
  }

  void swap_screens (int key_pressed) {
    if (key_pressed == 0) {
      if (CURRENT_PLUGIN == PLUGIN_SAMPLER) {
        CURRENT_PLUGIN = PLUGIN_SUBTRACTIVE;

      } else {
        CURRENT_PLUGIN = PLUGIN_SAMPLER;
      }
    }
  }
    
};

#include<unistd.h> //TODO remove (useless library?)

int main() {
  // MyApp app;

  // Start audio
  // app.configureAudio(44100., AUDIO_BLOCK_SIZE, 2, 0);

  // Set up sampling rate for Gamma objects
  // Domain::master().spu(app.audioIO().framesPerSecond());

  // app.start();

  CAT9555 cat000 = CAT9555(0b00100000);
  CAT9555 cat001 = CAT9555(0b00100001);

  while (true) {
    cat000.update();
    cat001.update();
    unsigned int microsecond = 500000;
    usleep(microsecond);//sleeps for 3 second
  }
}
