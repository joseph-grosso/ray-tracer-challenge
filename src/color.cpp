#include "color.hpp"

// Chapter 2: Colors and Canvas
Color::Color(float red, float green, float blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
};

bool operator==(Color lhs, Color rhs) {
  return equalByEpsilon(lhs.red, rhs.red, 1.0 / 255.0) &&
         equalByEpsilon(lhs.green, rhs.green, 1.0 / 255.0) &&
         equalByEpsilon(lhs.blue, rhs.blue, 1.0 / 255.0);
};

Color operator+(Color lhs, Color rhs) {
  return Color(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue);
};

Color operator-(Color lhs, Color rhs) {
  return Color(lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue - rhs.blue);
};

Color operator*(Color color, float a) {
  return Color(color.red * a, color.green * a, color.blue * a);
};

Color operator*(float a, Color color) {
  return Color(color.red * a, color.green * a, color.blue * a);
};

// Hadamard/Schur Product
Color operator*(Color lhs, Color rhs) {
  return Color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
};

// Chapter 6: Light and Shading
std::string Color::to_string() {
  return "Color(red=" + std::to_string(red) +
         ", green=" + std::to_string(green) + ", blue=" + std::to_string(blue) +
         ")";
};

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Color &m, std::ostream *os) {
  Color &ref = const_cast<Color &>(m);
  *os << ref.to_string();
};
