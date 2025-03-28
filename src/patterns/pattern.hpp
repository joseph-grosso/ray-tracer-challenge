#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "tuple.hpp"

class Shape;

class Pattern {
 private:
  Matrix transform;
  Matrix transform_inverse;

 public:
  Pattern(Matrix t = identity_matrix(4))
      : transform(t), transform_inverse(t.inverse()){};
  void set_transform(Matrix t) {
    transform = t;
    transform_inverse = t.inverse();
  };
  Matrix get_transform() { return transform; };
  Matrix get_transform_inverse() { return transform_inverse; };
  // The pattern_at function is purely virtual and must be
  // implemented by derived classes
  virtual Color pattern_at(Tuple p) = 0;  // must be a point, not vector
  Color pattern_at_shape(Shape *object, Tuple point_);
};
