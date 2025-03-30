#pragma once

#include <omp.h>

#include <string>
#include <vector>

#include "canvas.hpp"
#include "color.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"
#include "world.hpp"

// Chapter 7: Making a Scene
class Camera {
 private:
  Matrix transform;
  Matrix inverse_transform;

 public:
  // Attributes
  float half_width;
  float half_height;
  unsigned int hsize;
  unsigned int vsize;
  float field_of_view;
  float pixel_size;
  Matrix get_transform() { return transform; };
  void set_transform(Matrix t) {
    transform = t;
    inverse_transform = t.inverse();
  };
  Matrix get_transform_inverse() { return inverse_transform; };
  // Methods
  Camera(unsigned int hsize, unsigned int vsize, float field_of_view);
  Ray ray_for_pixel(int px, int py);
  Canvas render(World w, int reflections = 5);
};
