#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "canvas.h"
#include "intersection.h"
#include "matrix.h"
#include "sphere.h"
#include "transform.h"
#include "tuple.h"

using namespace std::chrono;

int main() {
  // Create camera
  Tuple camera_origin = point(0, 0, 5);

  // Define the limits of the "screen"
  Tuple bot_left = point(-5, -5, -5);
  Tuple top_right = point(5, 5, -5);

  // Define how we're going to move the ray along the canvas
  Tuple right_movement = vector(10, 0, 0);
  Tuple up_movement = vector(0, 10, 0);

  // Define the sphere and set its transform
  Sphere s = Sphere();
  Matrix t = translation_matrix(0, 1, -1);
  Matrix shear = shearing_matrix(2, 0, 0, 0, 0, 0);
  s.set_transform(shear);

  // Define the canvas
  unsigned int canv_x = 100, canv_y = 100;
  Canvas c(canv_x, canv_y);

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "New image generation starting!" << std::endl;

  Tuple current_point;
  Ray current_ray(camera_origin, bot_left - camera_origin);

  // Track how long the actual loops took
  auto start = high_resolution_clock::now();

  for (int i = 0; i < canv_x; i++) {
    for (int j = 0; j < canv_y; j++) {
      // Get the new ray
      current_point =
          bot_left + (right_movement * i / canv_x) + (up_movement * j / canv_y);
      current_ray = Ray(camera_origin, current_point - camera_origin);

      // Check if it hit the sphere
      Intersections xs = intersect(&s, current_ray);

      if (xs.count > 0) {
        c.write_pixel(Color(1, 0, 0), i, canv_y - j);
      };
    };
  };
  auto stop = high_resolution_clock::now();

  std::string filename = "transformed_circle.ppm";
  c.write_to_ppm(filename);

  std::cout << "Charted at " << filename << std::endl;

  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << " microseconds." << std::endl;
  std::cout << duration.count() / 1000000.0 << " seconds." << std::endl;
  std::cout << duration.count() / (canv_x * canv_y)
            << " microseconds per pixel." << std::endl;

  return 0;
}
