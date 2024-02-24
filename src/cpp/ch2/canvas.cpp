#include "tuple.h"
#include "canvas.h"
#include <vector>
#include <cmath>


// Chapter 1: Tuples, Vectors and Points
Canvas::Canvas(unsigned int width, unsigned int height) {
    this -> width = width;
    this -> height = height;
    this -> _canvas = std::vector<std::vector<Color>> (width);
    for (int i=0;i<width;i++) {
        _canvas[i] = std::vector<Color> (height);
    };
}

unsigned int Canvas::get_width() {
    return width;
}

unsigned int Canvas::get_height() {
    return height;
}

Color Canvas::get_point(unsigned int x, unsigned int y) {
    return _canvas[x][y];
}

Color Canvas::set_point(Color color, unsigned int x, unsigned int y) {
    _canvas[x][y] = color;
}
