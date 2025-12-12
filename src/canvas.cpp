#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "canvas.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tuple.hpp"

// Chapter 1: Tuples, Vectors and Points
Canvas::Canvas(unsigned int width, unsigned int height) {
  this->width = width;
  this->height = height;
  this->_canvas = std::vector<std::vector<Color>>(width);
  for (int i = 0; i < width; i++) {
    _canvas[i] = std::vector<Color>(height);
  };
}

unsigned int Canvas::get_width() { return width; }

unsigned int Canvas::get_height() { return height; }

Color Canvas::pixel_at(unsigned int x, unsigned int y) { return _canvas[x][y]; }

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
      std::string red = std::to_string(scale_color(col.red));
      std::string green = std::to_string(scale_color(col.green));
      std::string blue = std::to_string(scale_color(col.blue));
      if (line.length() + red.length() + 1 > 70) {
        content += line + "\n";
        line.clear();
        line += red;
      } else if (line.length() == 0) {
        line += red;
      } else {
        line += " " + red;
      };
      if (line.length() + green.length() + 1 > 70) {
        content += line + "\n";
        line.clear();
        line += green;
      } else if (line.length() == 0) {
        line += green;
      } else {
        line += " " + green;
      };
      if (line.length() + blue.length() + 1 > 70) {
        content += line + "\n";
        line.clear();
        line += blue;
      } else if (line.length() == 0) {
        line += blue;
      } else {
        line += " " + blue;
      };
    };
    content += line + "\n";
    line.clear();
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

void Canvas::write_to_ppm(std::string filename) {
  std::string ppm_data = canvas_to_ppm();
  std::ofstream out(filename);
  out << ppm_data;
  out.close();
  return;
};

void Canvas::write_to_png(std::string filename) {
  // Allocate buffer for 24-bit RGB image (3 bytes per pixel)
  unsigned char* png_data = new unsigned char[width * height * 3];

  // Fill the buffer with pixel data
  unsigned int offset = 0;
  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < width; x++) {
      Color col = _canvas[x][y];
      png_data[offset] = scale_color(col.red);
      png_data[offset + 1] = scale_color(col.green);
      png_data[offset + 2] = scale_color(col.blue);
      offset += 3;
    }
  }

  // Write PNG file using stb_image_write
  int result =
      stbi_write_png(filename.c_str(), width, height, 3, png_data, width * 3);

  // Clean up allocated memory
  delete[] png_data;

  // Handle errors
  if (!result) {
    std::cerr << "Error: Failed to write PNG file: " << filename << std::endl;
  }
};
