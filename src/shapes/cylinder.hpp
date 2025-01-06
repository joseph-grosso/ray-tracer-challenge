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
 private:
  bool check_cap(Ray r, float t);

 public:
  // Attributes
  float minimum;
  float maximum;
  bool closed;
  // Methods
  Cylinder(Matrix t = identity_matrix(4),
           float min = -std::numeric_limits<float>::infinity(),
           float max = std::numeric_limits<float>::infinity(),
           bool closed_ = false, Material m = Material(),
           bool throws_shadow = true)
      : Shape(t, m, throws_shadow),
        minimum{min},
        maximum{max},
        closed{closed_} {};
  // TODO: get more classes to use the approach above for setting vars in the
  // constructor
  float get_minimum() { return minimum; };
  float get_maximum() { return maximum; };
  float get_closed() { return maximum; };
  void set_minimum(float minimum) { this->minimum = minimum; };
  void set_maximum(float maximum) { this->maximum = maximum; };
  void set_closed(bool closed) { this->closed = closed; };
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p) { return local_normal_at(p.x, p.y, p.z); };
  Intersections local_intersect(Ray r);
  void intersect_caps(Ray ray, std::vector<Intersection> *xs);
};
