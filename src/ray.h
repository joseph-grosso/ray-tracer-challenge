#pragma once

#include "matrix.h"
#include "tuple.h"

#include <string>
#include <vector>

// Chapter 5: Rays
class Ray {
private:
  Tuple origin;
  Tuple direction;

public:
  // Methods
  // TODO: Create a default construction of the Ray class
  Ray(Tuple origin, Tuple direction);
  Tuple get_origin();
  Tuple get_direction();
  Tuple position(float t);
  Ray transform(Matrix m);
};
