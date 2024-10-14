#include "ray.h"
#include "matrix.h"
#include "tuple.h"
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

// Chapter 5: Rays
Ray::Ray(Tuple origin, Tuple direction) {
  if (!origin.isPoint()) {
    throw std::invalid_argument(
        "Origin Error: origin argument must be a point.");
  };
  if (!direction.isVector()) {
    throw std::invalid_argument(
        "Direction Error: direction argument must be a vector.");
  };
  this->origin = origin;
  this->direction = direction;
};

Tuple Ray::get_origin() { return origin; };

Tuple Ray::get_direction() { return direction; };

Tuple Ray::position(float t) { return origin + direction * t; };

Ray Ray::transform(Matrix m) {
  // TODO: Add size checking code
  return Ray(m * origin, m * direction);
};
