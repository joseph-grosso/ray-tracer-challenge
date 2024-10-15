#include "pattern.hpp"

#include "shape.h"

// Get the pattern at a point using the normal of a shape
Color Pattern::pattern_at_shape(Shape *object, Tuple point_) {
  Tuple obj_point = (*object).get_transform().inverse() * point_;
  Tuple pattern_point = get_transform().inverse() * obj_point;

  return pattern_at(pattern_point);
}
