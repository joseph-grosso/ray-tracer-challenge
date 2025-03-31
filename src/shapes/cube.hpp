#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "intersection.hpp"
#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "tuple.hpp"

// Chapter 12: Cubes
class Cube : public Shape {
 public:
  // Methods
  Cube(Matrix t = identity_matrix(), Material m = Material(),
       bool throws_shadow = true)
      : Shape(t, m, throws_shadow){};
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p, Intersection i = Intersection()) {
    return local_normal_at(p.x(), p.y(), p.z());
  };
  Intersections local_intersect(Ray r);

 private:
  std::tuple<float, float> check_axis(float origin, float direction);
};
