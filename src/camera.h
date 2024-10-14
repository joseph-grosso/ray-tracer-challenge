#pragma once

#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "ray.h"
#include "tuple.h"
#include "world.h"
#include <string>
#include <vector>

// Chapter 7: Making a Scene
class Camera {
public:
  // Attributes
  float half_width;
  float half_height;
  unsigned int hsize;
  unsigned int vsize;
  float field_of_view;
  Matrix transform;
  float pixel_size;
  // Methods
  Camera(unsigned int hsize, unsigned int vsize, float field_of_view);
  Ray ray_for_pixel(int px, int py);
  Canvas render(World w);
};
