#include "pattern.hpp"

#include "shape.hpp"

// Get the pattern at a point using the normal of a shape
Color Pattern::pattern_at_shape(Shape *object, Tuple point_) {
  Tuple obj_point = object->get_transform_inverse() * point_;
  Tuple pattern_point = get_transform_inverse() * obj_point;

  return pattern_at(pattern_point);
}
