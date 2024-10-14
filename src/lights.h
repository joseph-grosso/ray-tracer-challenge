#pragma once

#include "color.h"
#include "tuple.h"

#include <cmath>

// Chapter 6: Lights and Shading
class PointLight {
private:
  Tuple position;
  Color intensity;

public:
  PointLight(Tuple position, Color intensity);
  Tuple get_position();
  Color get_intensity();
};
