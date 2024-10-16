#include "computation.hpp"

// Chapter 7: Building a World
Computation::Computation(float t, Shape *object, Tuple point, Tuple eyev,
                         Tuple normalv) {
  this->t = t;
  this->object = object;
  this->point = point;
  this->eyev = eyev;
  if (normalv.dot(eyev) < 0) {
    this->inside = true;
    this->normalv = -normalv;
  } else {
    this->inside = false;
    this->normalv = normalv;
  };
  // TODO: Create epsilon constant that is shared around the codebase
  // TODO: Fix the shading function to
  // * make epsilon here smaller
  // * Reduce acne when epsilon is smaller
  this->over_point = this->point + this->normalv * 0.002;  // EPSILON
};
