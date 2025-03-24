#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.h"

using namespace std::chrono;

// First basic plane image; same as chapter 7
int main() {
  // Define the spheres
  // floor
  Plane floor = Plane(identity_matrix(4), Material(Color(1, 0.9, 0.9),  // color
                                                   0.1,  // ambient
                                                   0.5,  // diffuse
                                                   0,    // specular
                                                   0     // shininess
                                                   ));

  // First (Large, Green) Sphere
  Sphere middle = Sphere();
  middle.set_transform(translation_matrix(-0.5, 1, 0.5));
  middle.set_material(Material(Color(0.1, 1, 0.5),  // color
                               0.1,                 // ambient
                               0.7,                 // diffuse
                               0.3,                 // specular
                               200.0                // shininess
                               ));

  // Second (Medium, Green) Sphere
  Sphere right = Sphere();
  right.set_transform(translation_matrix(1.5, 0.5, -0.5) *
                      scaling_matrix(0.5, 0.5, 0.5));
  right.set_material(Material(Color(0.5, 1, 0.1),  // color
                              0.1,                 // ambient
                              0.7,                 // diffuse
                              0.3,                 // specular
                              200.0                // shininess
                              ));

  // Second (Small, Red) Sphere
  Sphere left = Sphere();
  left.set_transform(translation_matrix(-1.5, 0.33, -0.75) *
                     scaling_matrix(0.33, 0.33, 0.33));
  left.set_material(Material(Color(1, 0.8, 0.1),  // color
                             0.1,                 // ambient
                             0.7,                 // diffuse
                             0.3,                 // specular
                             200.0                // shininess
                             ));

  // Add a light source
  PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));

  // Create camera
  unsigned int x = 128;
  unsigned int y = 72;
  Camera camera(x, y, M_PI / 3);
  camera.transform =
      view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{&floor, &middle, &left, &right}, light);

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
