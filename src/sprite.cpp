#include "include/sprite.hpp"

sprite:: sprite() {
    
}

void sprite:: render(plot& p) {
    if (image.width() > plot::width || image.height() > plot::height) {
        std::cout<<"ImAGE TOO BIG!"<<std::endl;;
        return;
    }   

    int x_local = x_position + (image.width())/2;
    int y_local = y_position + (image.height())/2;

    int position = x_local * plot::width + y_local;
    for (int y=image.height()-1;y>=0;y--) {
        for (int x=image.width()-1;x>=0;x--) {

            int red = get_image_index(x, y);
            int green = red + 1;
            int blue = red + 2;
            int a = red + 3;

            if (a!=0) {
                al::Color c (image.array()[red]/255., image.array()[green]/255., image.array()[blue]/255., image.array()[a]/255.);
                p.plot_pixel(c, x_local - x, y_local- y);
            }
        }
    }
}


sprite:: sprite(std::string _filename, int x, int y) {
    
    x_position = x;
    y_position = y;

    filename = _filename.c_str();

    image = al::Image(filename);

    if (image.array().size() == 0) {
      std::cout << "failed to load image" << std::endl;
    }
    std::cout << "loaded image size: " << image.width() << ", "
         << image.height() << std::endl;

    int temp = 0;
    for (int i : image.array()) {
      temp++;
      std::cout<<i<<" ";
      if (temp%4==0) {
        temp = 0; std::cout<<std::endl;
      }
    }
    
}

int sprite:: get_image_index (int x, int y) {
    return ((y * image.width()) + x) * 4; //stride = 4
}