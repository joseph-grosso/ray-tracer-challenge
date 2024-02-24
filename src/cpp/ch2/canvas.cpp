#include "tuple.h"
#include "canvas.h"
#include <vector>
#include <cmath>


// Chapter 1: Tuples, Vectors and Points
Canvas::Canvas(unsigned int width, unsigned int height) {
    this -> width = width;
    this -> height = height;
    this -> _canvas = std::vector<Color> (width);
;
}

unsigned int Canvas::get_width() {
    return width;
}

unsigned int Canvas::get_height() {
    return height;
}

Color Canvas::get_point(unsigned int x, unsigned int y) {
    return _canvas[x];
}

