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

// Chapter 13: Cylinder
class Cylinder : public Shape {
 public:
  Cylinder(Matrix t = identity_matrix(4), Material m = Material(),
           bool throws_shadow = true)
      : Shape(t, m, throws_shadow){};
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p) { return local_normal_at(p.x, p.y, p.z); };
  Intersections local_intersect(Ray r);

 private:
  std::tuple<float, float> check_axis(float origin, float direction);
};
