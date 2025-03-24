#pragma once

#include <string>
#include <vector>

#include "intersection.hpp"
#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "tuple.hpp"

// Chapter 5: Rays
class Sphere : public Shape {
 private:
  Tuple center;
  float radius;

 public:
  // Methods
  Sphere(Matrix t = identity_matrix(4), Material m = Material(),
         bool throws_shadow = true)
      : Shape(t, m, throws_shadow) {
    this->center = point(0, 0, 0);
    this->radius = 1.0;
  };
  // Sphere(Matrix t) : Sphere(t, Material()) {};
  Sphere(Material m) : Sphere(identity_matrix(4), m){};
  Tuple get_center();
  float get_radius();
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p, Intersection i = Intersection());
  std::string to_string();
  Intersections local_intersect(Ray r);
};

bool operator==(Sphere lhs, Sphere rhs);
bool operator!=(Sphere lhs, Sphere rhs);

Sphere glass_sphere(Matrix m = identity_matrix(4), float refractive_index = 1.5,
                    float reflective = 0.0);
