#include "tuple.h"
#include "canvas.h"
#include <vector>
#include <cmath>
#include <iostream>


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

Color Canvas::pixel_at(unsigned int x, unsigned int y) {
    return _canvas[x][y];
}

void Canvas::write_pixel(Color color, unsigned int x, unsigned int y) {
    _canvas[x][y] = color;
    return;
}

std::string Canvas::ppm_header() {
    std::string header = "P3\n";
    header += std::to_string(width) + " " + std::to_string(height) + "\n";
    header += "255\n";
    return header;
};

std::string Canvas::ppm_content() {
    std::string content;
    std::string line;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color col = _canvas[i][j];
            line += std::to_string(scale_color(col.red));
            if (line.length() < 70) {
                line += " ";
            } else {
                content += line + "\n";
                line.clear();
            };
            line += std::to_string(scale_color(col.green));
            if (line.length() < 70) {
                line += " ";
            } else {
                content += line + "\n";
                line.clear();
            };
            line += std::to_string(scale_color(col.blue));
            if (line.length() < 70) {
                line += " ";
            } else {
                content += line + "\n";
                line.clear();
            };
        };
        content += line + "\n";
        line.clear();

    };
    if (line != "") {
        content += "\n";
    };
    return content;
}

std::string Canvas::canvas_to_ppm() {
    std::string ppm = ppm_header();
    ppm += ppm_content();
    return ppm;
};

unsigned int Canvas::scale_color(float color_value) {
    if (color_value < 0) {
        return 0;
    };
    unsigned int scaled_value = color_value * 256;
    if (scaled_value > 255) {
        return 255;
    };
    return scaled_value;
};
