#ifndef PLOT_HPP
#define PLOT_HPP

#include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Image.hpp"
#include <vector>
#include <cstdint>
#include <algorithm> 
#include <iterator>

class plot  {

  public:
    static const int width = 240;
    static const int height = 160;
    plot();
    void init();
    void render(al::Graphics& g);
    void reset_buffer();
    void plot_pixel(al::Color c, int x, int y);
    void plot_line(al::Color c, int x_start, int y_start, int x_end, int y_end);

  protected:
    al::Texture tex;
    al::Mesh mesh;
    int stride;
    std::vector<uint8_t> pixels;
};

#endif