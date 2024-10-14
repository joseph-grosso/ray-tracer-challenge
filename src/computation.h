#pragma once

#include "tuple.h"
#include <vector>

class Shape;
// Chapter 7: Building a World
class Computation {
public:
  // Attributes
  float t;
  Shape *object;
  Tuple point;
  Tuple over_point;
  Tuple eyev;
  Tuple normalv;
  bool inside;
  Computation(float t, Shape *object, Tuple point, Tuple eyev, Tuple normalv);
};
