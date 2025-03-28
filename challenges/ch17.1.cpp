#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Glass ball has no shadow - test
int main() {
  // base patterns
  SolidPattern off_white = SolidPattern(Color(0.9, 0.9, 0.9));

  SolidPattern red_d = SolidPattern(Color(1.0, 0.0, 0.0));
  SolidPattern blue_d = SolidPattern(Color(0.0, 0.0, 1.0));

  // Define the objects
  // Floor Plane
  Plane floor = Plane(identity_matrix(4), Material(&off_white));

  // glass_sphere
  Sphere s1 = Sphere(
      translation_matrix(0.5, 0.75, 0) * scaling_matrix(0.75, 0.75, 0.75),
      Material(&red_d));
  Sphere s2 = Sphere(translation_matrix(-1, 1, 0), Material(&blue_d));

  // Add a light source
  PointLight light = PointLight(point(-7, 7, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 10;
  unsigned int x = ratio * 30;
  unsigned int y = ratio * 30;
  Camera camera(x, y, M_PI / 8);
  camera.transform =
      view_transform(point(2, 3, -5), point(1, 1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{&floor, &s1, &s2}, light);

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "New image generation starting!" << std::endl;

  // Track how long the actual loops took
  auto start = high_resolution_clock::now();

  // Render the result
  Canvas image = camera.render(w);

  auto stop = high_resolution_clock::now();

  std::string filename = "values.ppm";
  image.write_to_ppm(filename);

  std::cout << "Charted at " << filename << std::endl;

  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << " microseconds." << std::endl;
  std::cout << duration.count() / 1000000.0 << " seconds." << std::endl;
  std::cout << duration.count() / (x * y) << " microseconds per pixel."
            << std::endl;

  return 0;
}
