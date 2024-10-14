#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

// Chapter 1: Tuples, Vectors and Points
// Equality test
bool equalByEpsilon(float a, float b, float epsilon = 0.001);

class Tuple {
public:
  // Attributes
  float x;
  float y;
  float z;
  float w;
  // Methods
  // TODO: Learn why virtual_cannon.cpp fails to compile when your tuple
  // constructor doesn't have default values
  // Tuple(float x, float y, float z, float w);
  Tuple(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
  bool isPoint();
  bool isVector();
  float magnitude();
  Tuple normalize();
  float dot(Tuple b);
  Tuple cross(Tuple b);
  std::string to_string();
  Tuple reflect(Tuple normal);
};

// Functions to create tuples
Tuple point(float x, float y, float z);
Tuple vector(float x, float y, float z);

// Arithmetic operators
bool operator==(Tuple lhs, Tuple rhs);
Tuple operator+(Tuple lhs, Tuple rhs);
Tuple operator-(Tuple tup);
Tuple operator-(Tuple lhs, Tuple rhs);
Tuple operator*(Tuple tup, float a);
Tuple operator*(float a, Tuple tup);
Tuple operator/(Tuple tup, float a);

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Tuple &m, std::ostream *os);
