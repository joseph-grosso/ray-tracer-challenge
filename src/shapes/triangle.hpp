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

// Chapter 15: Triangle sections
class Triangle : public Shape {
 private:
 public:
  // Attributes
  Tuple p1;
  Tuple p2;
  Tuple p3;
  Tuple e1;
  Tuple e2;
  Tuple normal;
  // Methods
  Triangle(Tuple p1_, Tuple p2_, Tuple p3_, Matrix t = identity_matrix(),
           Material m = Material(), bool throws_shadow = true)
      : Shape(t, m, throws_shadow),
        p1{p1_},
        p2{p2_},
        p3{p3_},
        e1{p2_ - p1_},
        e2{p3_ - p1_},
        normal{e2.cross(e1).normalize()} {};
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p, Intersection i = Intersection()) {
    return local_normal_at(p.x(), p.y(), p.z());
  };
  Intersections local_intersect(Ray r);
};
