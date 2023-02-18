#pragma once
#include "al/graphics/al_Graphics.hpp"
#include "al/io/al_AudioIO.hpp"
#include "al/io/al_Window.hpp"

namespace box {

class Plugin {

public:
    // Plugin();
    // Plugin(const Plugin&);
    // Plugin(Plugin&&);
    // Plugin& operator=(const Plugin&);
    // Plugin& operator=(Plugin&&);
    // virtual ~Plugin() = 0;

    virtual void onProcess(al::AudioIOData &io) = 0;
    virtual void onProcess(al::Graphics& g) = 0;
    virtual void onTriggerOn(const al::Keyboard &k) = 0;
    virtual void onTriggerOff(const al::Keyboard &k) = 0;
};

} // namespace box