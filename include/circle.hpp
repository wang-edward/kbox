#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "include/plot.hpp"

class circle {

    public:
        circle();
        circle(int x, int y, int radius, al::Color c);
        void render_outline(plot& p);
        void render(plot& p);
        void transform_position(int x_center, int y_center);
        void transform_radius(int radius);
        void transform_color(al::Color c);
        void draw(al::Color c, plot& p);
        void draw_circle(int x_center, int y_center, int radius, al::Color c, plot& p);
        void draw_circle_lines(int cx, int cy, int x, int y, al::Color pix, plot& p);
        void draw_circle_points(int cx, int cy, int x, int y, al::Color pix, plot& p);

    protected:
        int x_position;
        int y_position;
        int radius;
        al::Color color;
};

#endif