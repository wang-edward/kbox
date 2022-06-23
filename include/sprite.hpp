#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Image.hpp"
#include <vector>
#include <cstdint>
#include <algorithm> 
#include <iterator>
#include <string>

#include "plot.hpp"

class sprite  {

  public:


    sprite();
    sprite(std::string _filename, int x, int y);

    void render(plot& p);

    void draw_image(int x, int y, al::Image image, plot& p);

    int get_image_index (int x, int y);

    protected:
      const char* filename;
      al::Image image;
      int x_position;
      int y_position;

  
};

#endif