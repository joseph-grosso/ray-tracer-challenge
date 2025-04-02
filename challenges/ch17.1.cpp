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

  SolidPattern v_light_blue =
      SolidPattern(Color(81.0 / 100.0, 93.0 / 100.0, 93.0 / 100.0));
  SolidPattern light_blue =
      SolidPattern(Color(78.0 / 100.0, 94.0 / 100.0, 100.0 / 100.0));
  SolidPattern sky_blue =
      SolidPattern(Color(67.0 / 100.0, 91.0 / 100.0, 100.0 / 100.0));
  SolidPattern pastel_purple =
      SolidPattern(Color(78.0 / 100.0, 72.0 / 100.0, 89.0 / 100.0));

  // floor patterns
  SolidPattern green = SolidPattern(Color(0.56, 0.91, 0.60));
  SolidPattern orange = SolidPattern(Color(1, 0.55, 0));

  // wall patterns
  CheckersPattern wall_pat =
      CheckersPattern(&light_blue, &sky_blue, identity_matrix());
  PermutationPattern permuted_sky = PermutationPattern(&wall_pat);

  // Define the objects
  // Floor Plane
  Plane floor = Plane(translation_matrix(0, -1, 0),
                      Material(&pastel_purple, Color(1, 0.9, 0.9),  // color
                               0.1,                                 // ambient
                               0.5,                                 // diffuse
                               0,                                   // specular
                               0                                    // shininess
                               ));

  Plane sky = Plane(translation_matrix(0, 20, 0), Material(&v_light_blue));

  Sphere metal_ball = metal_sphere(translation_matrix(-1, 1, 0));
  // Glass floor
  Plane glass_floor = Plane(identity_matrix(), glass_material(1.5, 0.6), false);
  // back_wall
  Sphere walls = Sphere(scaling_matrix(60.0, 60.0, 60.0),
                        Material(&light_blue, Color(0.66, 0, 0.34),  // color
                                 0.1,                                // ambient
                                 0.5,                                // diffuse
                                 0,                                  // specular
                                 0  // shininess
                                 ));

  SolidPattern solid_green = SolidPattern(Color(0, 1, 0));
  SolidPattern blue = SolidPattern(Color(0.24, 0.51, 0.99));
  PerlinPattern perl =
      PerlinPattern(&green, &blue, 12345, scaling_matrix(0.25, 0.25, 0.25));

  // Floor Plane
  Sphere world_sphere =
      Sphere(translation_matrix(1, 1, 0), Material(Color(0.5, 0, 0),  // color
                                                   0.1,               // ambient
                                                   0.9,               // diffuse
                                                   0.9,  // specular
                                                   300,  // shininess
                                                   0.5));

  // Glass ball
  Sphere glass_ball = glass_sphere(translation_matrix(0, 1, -2.7));

  // Add a light source
  PointLight light = PointLight(point(10, 10, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 6;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 70;
  Camera camera(x, y, M_PI / 5);
  camera.set_transform(
      view_transform(point(0, 3, -10), point(0, 1, 0), vector(0, 1, 0)));

  // Create world
  World w(
      std::vector<Shape *>{
          &floor, &walls, &glass_floor,            // walls
          &metal_ball, &world_sphere, &glass_ball  // spheres
      },
      light);

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "New image generation starting!" << std::endl;

  // Track how long the actual loops took
  auto start = high_resolution_clock::now();

  // Render the result
  Canvas image = camera.render(w, 2);

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
