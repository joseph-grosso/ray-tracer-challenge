#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Perlin Noise test
int main() {
  SolidPattern green = SolidPattern(Color(0, 1, 0));
  SolidPattern blue = SolidPattern(Color(0, 0, 1));
  PerlinPattern perl =
      PerlinPattern(&green, &blue, 12345, scaling_matrix(0.25, 0.25, 0.25));

  // Define the objects
  // Floor Plane
  Sphere s =
      Sphere(identity_matrix(4), Material(&perl, Color(1, 0.9, 0.9),  // color
                                          0.1,                        // ambient
                                          0.5,                        // diffuse
                                          0,  // specular
                                          0   // shininess
                                          ));

  // Add a light source
  PointLight light = PointLight(point(10, 10, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 10;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 100;
  Camera camera(x, y, M_PI / 6);
  camera.transform =
      view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));

  // Create world
  World w(
      std::vector<Shape *>{
          &s,
      },
      light);

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
