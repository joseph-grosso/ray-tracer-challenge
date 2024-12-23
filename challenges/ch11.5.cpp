#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Fresnel effect test with walls
int main() {
  // base patterns
  SolidPattern white = SolidPattern(Color(1, 1, 1));
  SolidPattern grey = SolidPattern(Color(0.85, 0.85, 0.85));

  // floor patterns
  SolidPattern green = SolidPattern(Color(0.56, 0.91, 0.60));
  SolidPattern orange = SolidPattern(Color(1, 0.55, 0));

  CheckersPattern floor_pat =
      CheckersPattern(&green, &orange, identity_matrix(4));

  // wall patterns
  CheckersPattern wall_pat = CheckersPattern(&white, &grey, identity_matrix(4));

  // Define the objects
  // Floor Plane
  Plane floor = Plane(identity_matrix(4),
                      Material(&floor_pat, Color(1, 0.9, 0.9),  // color
                               0.1,                             // ambient
                               0.5,                             // diffuse
                               0,                               // specular
                               0                                // shininess
                               ));

  // Glass floor
  Plane glass_floor =
      Plane(translation_matrix(0, 1, 0), glass_material(), false);
  // back_wall
  Plane back_wall =
      Plane(translation_matrix(0, 0, 50) * rotation_x_matrix(M_PI / 2),
            Material(&wall_pat, Color(0.66, 0, 0.34),  // color
                     0.1,                              // ambient
                     0.5,                              // diffuse
                     0,                                // specular
                     0                                 // shininess
                     ));

  // Add a light source
  PointLight light = PointLight(point(10, 10, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 4;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 33;
  Camera camera(x, y, M_PI / 2.0);
  camera.transform =
      view_transform(point(0, 3, -10), point(0, 1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{&floor, &back_wall, &glass_floor}, light);

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
