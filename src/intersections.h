#pragma once

#include "intersection.h"
#include "ray.h"
#include <vector>

class Intersections {
public:
  Intersections() : Intersections(std::vector<Intersection>{}){};
  Intersections(std::vector<Intersection>);
  std::vector<Intersection> data;
  int count;
  Intersection operator[](int);
  Intersection hit();
};
