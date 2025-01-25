#include "triangle.hpp"

#include <iostream>

#include "intersection.hpp"

Intersections Triangle::local_intersect(Ray r) {
  std::vector<Intersection> xs = std::vector<Intersection>{};

  return Intersections(xs);
};

Tuple Triangle::local_normal_at(float x, float y, float z) { return normal; };
