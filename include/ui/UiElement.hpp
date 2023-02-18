#pragma once
#include "al/graphics/al_Graphics.hpp"
#include "al/io/al_Window.hpp"
namespace box {
class UiElement {
public:
private:
    virtual void onProcess(al::Graphics& g);
    virtual void onTriggerOn(const al::Keyboard &k);
    virtual void onTriggerOff(const al::Keyboard &k);

};

} // namespace box
