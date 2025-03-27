#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

// Chapter 1: Tuples, Vectors and Points
// Equality test
bool equalByEpsilon(float a, float b, float epsilon = 0.001);

#include <Eigen/Dense>

class Tuple {
 public:
  // Attributes
  Eigen::Vector4f values;

  // Methods
  Tuple(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
      : values(x, y, z, w) {}
  Tuple(Eigen::Vector4f values) : values(values){};
  bool isPoint() { return equalByEpsilon(values.w(), 1.0f); }
  bool isVector() { return equalByEpsilon(values.w(), 0.0f); }
  float magnitude() { return values.norm(); }
  Tuple normalize() { return Tuple(values.normalized()); }
  float dot(Tuple b) { return values.dot(b.values); }
  Tuple cross(Tuple b) {
    Eigen::Vector3f v1(values.x(), values.y(), values.z());
    Eigen::Vector3f v2(b.values.x(), b.values.y(), b.values.z());
    Eigen::Vector3f result = v1.cross(v2);
    return Tuple(result.x(), result.y(), result.z(), 0.0f);
  }
  std::string to_string() {
    return "Tuple(" + std::to_string(values.x()) + ", " +
           std::to_string(values.y()) + ", " + std::to_string(values.z()) +
           ", " + std::to_string(values.w()) + ")";
  }
  Tuple reflect(Tuple normal) {
    return Tuple(this->values - normal.values * 2.0f * this->dot(normal));
  }

  // Method to get value by field name
  float x() { return values.x(); };
  float y() { return values.y(); };
  float z() { return values.z(); };
  float w() { return values.w(); };
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
