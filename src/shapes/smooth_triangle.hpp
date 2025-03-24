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
#include "triangle.hpp"

// Chapter 15: Triangle sections
class SmoothTriangle : public Shape {
 private:
 public:
  // Attributes
  Tuple p1;
  Tuple p2;
  Tuple p3;
  Tuple n1;
  Tuple n2;
  Tuple n3;
  Tuple e1;
  Tuple e2;
  // Methods
  SmoothTriangle(Tuple p1_, Tuple p2_, Tuple p3_, Tuple n1_, Tuple n2_, Tuple n3_, Matrix t = identity_matrix(4),
           Material m = Material(), bool throws_shadow = true)
      : Shape(t, m, throws_shadow),
        p1{p1_},
        p2{p2_},
        p3{p3_},
        n1{n1_},
        n2{n2_},
        n3{n3_},
        e1{p2_ - p1_},
        e2{p3_ - p1_} {};
  Tuple local_normal_at(float x, float y, float z, Intersection i);
  Tuple local_normal_at(Tuple p, Intersection i) { return local_normal_at(p.x, p.y, p.z, i); };
  Intersections local_intersect(Ray r);
};
