#include "pattern.h"
#include "shape.h"

// Constructor
Pattern::Pattern(Matrix t) : transform(t) {}

// Set the transformation matrix
void Pattern::set_transform(Matrix t) {
    transform = t;
}

// Get the transformation matrix
Matrix Pattern::get_transform() {
    return transform;
}

// Get the pattern at a point using the normal of a shape
Color Pattern::pattern_at_shape(Shape * object, Tuple point_) {
    Tuple obj_point = (*object).get_transform().inverse() * point_;
    Tuple pattern_point = get_transform().inverse() * obj_point;

    return pattern_at(pattern_point);
}

// The pattern_at function is purely virtual and must be implemented by derived classes