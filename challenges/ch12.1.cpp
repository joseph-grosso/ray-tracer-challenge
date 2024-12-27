#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// cube room
int main() {
  // base patterns
  SolidPattern off_white = SolidPattern(Color(0.9, 0.9, 0.9));
  SolidPattern off_black = SolidPattern(Color(0.1, 0.1, 0.1));

  SolidPattern red_l = SolidPattern(Color(0.886, 0.247, 0.266));
  SolidPattern red_d = SolidPattern(Color(0.443, 0.121, 0.133));
  SolidPattern blue_l = SolidPattern(Color(0.678, 0.874, 1));
  SolidPattern blue_d = SolidPattern(Color(0.450, 0.584, 0.666));
  SolidPattern brown_l = SolidPattern(Color(0.41, 0.21, 0.0));
  SolidPattern brown_d = SolidPattern(Color(0.35, 0.15, 0.02));
  SolidPattern green = SolidPattern(Color(0.0, 1.0, 0.0));
  SolidPattern gray_w = SolidPattern(Color(0.33, 0.29, 0.31));

  // room patterns
  StripePattern stripe_pat_1 = StripePattern(
      &red_l, &red_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(M_PI / 3));
  StripePattern stripe_pat_2 = StripePattern(
      &blue_l, &blue_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(-M_PI / 3));
  PerlinPattern wall_pat =
      PerlinPattern(&brown_l, &brown_d, 0, scaling_matrix(0.1, 0.1, 0.1));
  PerlinPattern table_pat =
      PerlinPattern(&brown_l, &brown_d, 1, scaling_matrix(0.1, 0.1, 0.1));

  // Define the objects
  // roof and floor
  Cube roof_and_floor =
      Cube(scaling_matrix(100, 5, 100) * translation_matrix(0, 1, 0),
           Material(&gray_w, Color(0, 0, 0),  // color
                    0.1,                      // ambient
                    0.5,                      // diffuse
                    0,                        // specular
                    0                         // shininess
                    ));

  // walls
  Cube walls = Cube(scaling_matrix(7, 100, 7),
                    Material(&wall_pat, Color(0, 0, 0),  // color
                             0.1,                        // ambient
                             0.5,                        // diffuse
                             0,                          // specular
                             0                           // shininess
                             ),
                    false);

  // mirror
  Cube mirror = Cube(translation_matrix(0, 1, 7.9) * scaling_matrix(5, 3, 1) *
                         translation_matrix(0, 1, 0),
                     mirror_material());

  // tabletop
  Cube table_top =
      Cube(translation_matrix(0, 1.3, 5) * scaling_matrix(1, 0.2, 1) *
               translation_matrix(0, 1, 0),
           Material(&table_pat));

  // Add a light source
  PointLight light = PointLight(point(-1, 3, -4), Color(1, 1, 1));

  // Create camera
  int ratio = 3;
  unsigned int x = ratio * 70;
  unsigned int y = ratio * 70;
  Camera camera(x, y, M_PI / 1.8);
  camera.transform =
      view_transform(point(2, 5, -4), point(-0.5, 1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{&walls, &roof_and_floor, &mirror, &table_top},
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
