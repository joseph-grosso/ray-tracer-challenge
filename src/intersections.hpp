#pragma once

#include <vector>

#include "intersection.hpp"
#include "ray.hpp"

class Intersections {
 public:
  Intersections(std::vector<Intersection> = std::vector<Intersection>{});
  std::vector<Intersection> data;
  int count;
  Intersection operator[](int);
  Intersection hit();
  bool is_shadowed(float light_distance);
};
