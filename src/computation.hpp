#pragma once

#include <vector>

#include "tuple.hpp"

class Shape;
// Chapter 7: Building a World
class Computation {
 public:
  // Attributes
  float t;
  Shape *object;
  Tuple point;
  Tuple over_point;
  Tuple under_point;
  Tuple eyev;
  Tuple normalv;
  Tuple reflectv;
  bool inside;
  float n1;
  float n2;
  Computation(float t, Shape *object, Tuple point, Tuple eyev, Tuple normalv,
              Tuple reflectv, float n1, float n2);
  float schlick();
  std::string to_string();
};
