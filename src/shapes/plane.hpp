#pragma once

#include <cmath>
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

// Chapter 9: Planes
class Plane : public Shape {
 private:
  Tuple normal;
  Tuple point_inside;

 public:
  // Methods
  Plane(Matrix t = identity_matrix(4), Material m = Material(),
        bool throws_shadow = true)
      : Shape(t, m, throws_shadow) {
    this->normal = vector(0, 1, 0);
    this->point_inside = point(0, 0, 0);
  };
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p);
  // TODO: refactor when an intersection is done on a general "object" class
  // rather than just the sphere class.
  Intersections local_intersect(Ray r);
};

// bool operator==(Plane lhs, Plane rhs);
// bool operator!=(Plane lhs, Plane rhs);
