#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// perlin test
int main() {
  // base patterns
  SolidPattern off_white = SolidPattern(Color(0.9, 0.9, 0.9));
  SolidPattern off_black = SolidPattern(Color(0.1, 0.1, 0.1));
  CheckersPattern checkers =
      CheckersPattern(&off_white, &off_black, scaling_matrix(0.4, 0.4, 0.4));
  PermutationPattern p_checkers = PermutationPattern(&checkers, 0.2, 42);

  // globe
  Sphere globe_1 = Sphere(translation_matrix(-1.1, 0, 0),
                          Material(&checkers, Color(0, 0, 0), 0.3, 0.7));
  // globe
  Sphere globe_2 = Sphere(translation_matrix(1.1, 0, 0),
                          Material(&p_checkers, Color(0, 0, 0), 0.3, 0.7));

  // Create camera
  int ratio = 12;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 50;
  Camera camera(x, y, M_PI / 27);
  camera.transform =
      view_transform(point(0, 0, -40), point(0, 0, 0), vector(0, 1, 0));

  // Add a light source
  PointLight light = PointLight(point(10, 10, -40), Color(1, 1, 1));

  // Create world
  World w(std::vector<Shape *>{&globe_1, &globe_2}, light);

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "New image generation starting!" << std::endl;
  std::cout << "Pixels generated:" << x * y << std::endl;

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
