#include "include/circle.hpp"

circle:: circle() {
    std::cout<<"CIRClE NOT INIT"<<std::endl;
}

circle:: circle(int x, int y, int radius, al::Color c) {
    x_position = x;
    y_position = y;
    this->radius = radius;
    this->color = c;
}

void circle:: render_outline (plot& p) {
    if (radius==0) return;

    int x = 0; 
    int y = radius;
    int point = (5-radius * 4)/4;

    draw_circle_points(x_position, y_position, x, y, this->color, p);
    while (x < y) {
        x++;
        if (point<0) {
            point+=2*x + 1;
        } else {
            y--;
            point += 2*(x-y) + 1;
        }
        draw_circle_points(x_position, y_position, x, y, this->color, p);
    }
}

void circle:: render (plot& p) {
    // if (radius==NULL) {
    //     std::cout<<"NO RADIUS"<<std::endl;
    //     return;
    // }
    // if (x_position==NULL || y_position==NULL) {
    //     std::cout<<"NO POSITION"<<std::endl;
    //     return;
    // }
    // if (color==NULL) {
    //     std::cout<<"NO COLOR"<<std::endl;
    //     return;
    // }
    int x = 0; 
    int y = radius;
    int point = (5-radius * 4)/4;

    draw_circle_lines(x_position, y_position, x, y, this->color, p);
    while (x < y) {
        x++;
        if (point<0) {
            point+=2*x + 1;
        } else {
            y--;
            point += 2*(x-y) + 1;
        }
        draw_circle_lines(x_position, y_position, x, y, this->color, p);
    }
}

void circle::transform_position(int x_center, int y_center) {
    x_position = x_center;
    y_position = y_center;
}

void circle::transform_radius(int radius) {
    this->radius = radius;
}

void circle::transform_color(al::Color c) {
    this->color = c;
}

void circle::draw_circle_lines(int cx, int cy, int x, int y, al::Color pix, plot& p) {
    if (x==0) {
        p.plot_line(pix, cx, cy+y, cx, cy-y);
        p.plot_line(pix, cx+y, cy, cx-y, cy);

    } else if (x == y) {
        p.plot_line(pix, cx+x, cy+y, cx-x, cy+y);
        p.plot_line(pix, cx+x, cy-y, cx-x, cy-y);
    } else if (x < y) {
        p.plot_line(pix, cx+x, cy+y, cx-x, cy+y);
        p.plot_line(pix, cx+x, cy-y, cx-x, cy-y);
        p.plot_line(pix, cx+y, cy+x, cx-y, cy+x);
        p.plot_line(pix, cx+y, cy-x, cx-y, cy-x);
    }
}

void circle:: draw_circle_points(int cx, int cy, int x, int y, al::Color pix, plot& p) {
    if (x==0) {
      p.plot_pixel(pix, cx, cy + y);
      p.plot_pixel(pix, cx, cy - y);
      p.plot_pixel(pix, cx + y, cy);
      p.plot_pixel(pix, cx - y, cy);
    } else if (x == y) {
      p.plot_pixel(pix, cx + x, cy + y);
      p.plot_pixel(pix, cx - x, cy + y);
      p.plot_pixel(pix, cx + x, cy - y);
      p.plot_pixel(pix, cx - x, cy - y);
    } else if (x < y) {
      p.plot_pixel(pix, cx + x, cy + y);
      p.plot_pixel(pix, cx - x, cy + y);
      p.plot_pixel(pix, cx + x, cy - y);
      p.plot_pixel(pix, cx - x, cy - y);

      p.plot_pixel(pix, cx + y, cy + x);
      p.plot_pixel(pix, cx - y, cy + x);
      p.plot_pixel(pix, cx + y, cy - x);
      p.plot_pixel(pix, cx - y, cy - x);
    }
}