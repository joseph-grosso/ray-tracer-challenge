#pragma once

#include "tuple.h"
#include <vector>


// Chapter 2: Colors and Canvas
class Canvas {
    private:
        std::vector<Color> _canvas;
        // Attributes
        int width, height;
    public:
        // Methods
        Canvas(unsigned int width, unsigned int height);
        unsigned int get_width();
        unsigned int get_height();
        Color get_point(unsigned int x, unsigned int y);
};