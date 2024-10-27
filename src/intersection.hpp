#pragma once

#include <tuple>
#include <vector>

#include "computation.hpp"
#include "ray.hpp"

class Shape;
class Intersections;
class Intersection {
 private:
  bool empty;
  std::vector<float> compute_n1_and_n2(Intersections xs);

 public:
  Intersection();
  Intersection(float t, Shape *const obj);
  float t;
  // TODO: use OOP to generalize this object class
  Shape *object;
  bool is_empty();
  Computation prepare_computations(Ray r, Intersections xs);
};

bool operator==(Intersection lhs, Intersection rhs);
bool operator<(Intersection lhs, Intersection rhs);
