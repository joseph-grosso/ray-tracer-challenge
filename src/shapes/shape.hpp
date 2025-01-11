#pragma once

#include <random>
#include <string>
#include <vector>

#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"

// Chapter 9: Shapes and Planes
class Shape {
 protected:
  Matrix transformation;
  Material material;
  bool throws_shadow;

 public:
  // Attributes
  Shape *parent;
  // Methods
  Shape(Matrix t = identity_matrix(4), Material m = Material(),
        bool throws_shadow = true, Shape *parent = NULL);
  Shape(Material m) : Shape(identity_matrix(4), m){};
  Matrix get_transform();
  void set_transform(Matrix);
  Material get_material();
  void set_throws_shadow(bool);
  bool get_throws_shadow();
  void set_material(Material);
  Intersections intersect(Ray r);
  virtual Intersections local_intersect(Ray r) = 0;
  Tuple normal_at(Tuple p);
  Tuple normal_at(float x, float y, float z);
  virtual Tuple local_normal_at(Tuple p) = 0;
  Tuple world_to_object(Tuple p);
};
