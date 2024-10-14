#pragma once

#include "intersections.h"
#include "material.h"
#include "matrix.h"
#include "ray.h"
#include "tuple.h"

#include <random>
#include <string>
#include <vector>

// Chapter 9: Shapes and Planes
class Shape {
protected:
  Matrix transformation;
  Material material;

public:
  // Methods
  Shape(Matrix t = identity_matrix(4), Material m = Material());
  Shape(Matrix t) : Shape(t, Material()){};
  Shape(Material m) : Shape(identity_matrix(4), m){};
  Matrix get_transform();
  void set_transform(Matrix);
  Material get_material();
  void set_material(Material);
  Intersections intersect(Ray r);
  virtual Intersections local_intersect(Ray r) = 0;
  Tuple normal_at(Tuple p);
  Tuple normal_at(float x, float y, float z);
  virtual Tuple local_normal_at(Tuple p) = 0;
};
