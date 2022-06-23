#ifndef SINE_ENV_HPP
#define SINE_ENV_HPP


#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/io/al_AudioIO.hpp"
#include "al/scene/al_PolySynth.hpp"

using namespace gam;
using namespace al;



class SineEnv : public SynthVoice {
 public:
  SineEnv();

  // Note parameters
  SineEnv& freq(float v);

  // Audio processing function
  void onProcess(AudioIOData& io) override;

  // Graphics processing function
  void onProcess(Graphics& g) override;

  void onTriggerOn() override;

  void onTriggerOff() override;

 protected:
  float mAmp{0.2f};
  float mDur{1.5f};
  Sine<> mOsc;
  // Env<3> mAmpEnv{0.f, 0.5f, 1.f, 1.0f, 1.f, 2.0f, 0.f};
  Env<3> mAmpEnv{0.f, 0.2f, 1.f, 1.0f, 1.f, 0.5f, 0.f};


  Mesh mMesh;
};


#endif