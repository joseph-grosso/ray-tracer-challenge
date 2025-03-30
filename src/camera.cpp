#include "camera.hpp"

#include <math.h>

#include <iostream>
#include <string>
#include <vector>

Camera::Camera(unsigned int hsize, unsigned int vsize, float field_of_view) {
  // Computed values
  float half_view = tan(field_of_view / 2);
  float aspect = (float)hsize / vsize;

  if (aspect >= 1) {
    this->half_width = half_view;
    this->half_height = half_view / aspect;
  } else {
    this->half_width = half_view * aspect;
    this->half_height = half_view;
  };

  this->pixel_size = (this->half_width * 2) / hsize;

  // Raw values
  this->hsize = hsize;
  this->vsize = vsize;
  this->field_of_view = field_of_view;
};

Ray Camera::ray_for_pixel(int px, int py) {
  // The offset from the edge of the canvas to the pixel's center
  float xoffset = (float)((float)px + (float)0.5) * (float)pixel_size;
  float yoffset = (float)((float)py + (float)0.5) * (float)pixel_size;

  // The untransformed coordinates of the pixel in world space
  float world_x = half_width - xoffset;
  float world_y = half_height - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // and then compute the the ray's direction vector
  Tuple pixel = inverse_transform * point(world_x, world_y, -1);
  Tuple origin = inverse_transform * point(0, 0, 0);
  Tuple direction = (pixel - origin).normalize();

  return Ray(origin, direction);
};

Canvas Camera::render(World w, int reflections) {
  Canvas image(hsize, vsize);
#pragma omp parallel for collapse(2) num_threads(8)
  for (int x = 0; x < hsize; x++) {
    for (int y = 0; y < vsize; y++) {
      Ray r = ray_for_pixel(x, y);
      Color c = w.color_at(r, reflections);
      image.write_pixel(c, x, y);
    };
  };

  return image;
};
