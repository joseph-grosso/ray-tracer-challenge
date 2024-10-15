#pragma once

#include <vector>

#include "computation.hpp"
#include "ray.hpp"

class Shape;

class Intersection {
 private:
  bool empty;

 public:
  Intersection();
  Intersection(float t, Shape *const obj);
  float t;
  // TODO: use OOP to generalize this object class
  Shape *object;
  bool is_empty();
  Computation prepare_computations(Ray r);
};

bool operator==(Intersection lhs, Intersection rhs);
bool operator<(Intersection lhs, Intersection rhs);
