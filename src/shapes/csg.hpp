#pragma once

#include <bits/stdc++.h>

#include <string>
#include <vector>

#include "intersection.hpp"
#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "tuple.hpp"

// Chapter 16: CSG
class CSG : public Shape {
 private:
  std::string operation;
  Shape *left;
  Shape *right;

 public:
  // Methods
  CSG(std::string operation_, Shape *left_, Shape *right_,
      Matrix t = identity_matrix(4))
      : Shape(t), operation{operation_}, left{left_}, right{right_} {
    left->parent = this;
    right->parent = this;
  };
  Shape *get_left() { return left; };
  Shape *get_right() { return right; };
  std::string get_operation() { return operation; };
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p, Intersection i = Intersection());
  std::string to_string();
  Intersections local_intersect(Ray r);
};