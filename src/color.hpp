#pragma once

#include <cmath>
#include <stdexcept>
#include <string>
// TODO: is this necessary?
#include "tuple.hpp"

// Chapter 2: Colors
class Color {
 public:
  // Attributes
  float red, green, blue;
  // Methods
  Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f);
  std::string to_string();
};

// Arithmetic operators
bool operator==(Color lhs, Color rhs);
Color operator+(Color lhs, Color rhs);
Color operator-(Color lhs, Color rhs);
Color operator*(Color color, float a);
Color operator*(float a, Color color);
Color operator*(Color lhs, Color rhs);

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Color &m, std::ostream *os);
