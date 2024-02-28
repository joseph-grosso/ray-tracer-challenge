#pragma once

#include "tuple.h"
#include <vector>
#include <iostream>


// Chapter 2: Colors and Canvas
class Canvas {
    private:
        // Attributes
        unsigned int width, height;
        std::vector<std::vector<Color>> _canvas;
        // Methods
        std::string ppm_header();
        std::string ppm_content();
        unsigned int scale_color(float color_value);
    public:
        // Methods
        Canvas(unsigned int width, unsigned int height);
        unsigned int get_width();
        unsigned int get_height();
        Color pixel_at(unsigned int x, unsigned int y);
        void write_pixel(Color color, unsigned int x, unsigned int y);
        std::string canvas_to_ppm();
        void write_to_ppm(std::string filename = "canvas.ppm");
};