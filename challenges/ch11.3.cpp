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
  SolidPattern off_black = SolidPattern(Color(0.1, 0.1, 0.1));

  SolidPattern red_l = SolidPattern(Color(0.886, 0.247, 0.266));
  SolidPattern red_d = SolidPattern(Color(0.443, 0.121, 0.133));
  SolidPattern blue_l = SolidPattern(Color(0.678, 0.874, 1));
  SolidPattern blue_d = SolidPattern(Color(0.450, 0.584, 0.666));

  // floor patterns
  StripePattern stripe_pat_1 = StripePattern(
      &red_l, &red_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(M_PI / 3));
  StripePattern stripe_pat_2 = StripePattern(
      &blue_l, &blue_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(-M_PI / 3));
  CheckersPattern floor_pat = CheckersPattern(&stripe_pat_2, &stripe_pat_1,
                                              rotation_y_matrix(-M_PI / 8));

  // wall patterns
  CheckersPattern wall_pat =
      CheckersPattern(&off_white, &off_black, identity_matrix());

  // Define the objects
  // Floor Plane
  Plane floor = Plane(identity_matrix(),
                      Material(&floor_pat, Color(1, 0.9, 0.9),  // color
                               0.1,                             // ambient
                               0.5,                             // diffuse
                               0,                               // specular
                               0                                // shininess
                               ));

  // left_mid_wall
  Plane left_mid_wall =
      Plane(translation_matrix(0, 0, 8) * rotation_y_matrix(-M_PI / 4) *
                rotation_x_matrix(M_PI / 2),
            Material(&wall_pat, Color(0.66, 0, 0.34),  // color
                     0.1,                              // ambient
                     0.5,                              // diffuse
                     0,                                // specular
                     0                                 // shininess
                     ));

  // right_mid_wall
  Plane right_mid_wall =
      Plane(translation_matrix(0, 0, 8) * rotation_y_matrix(M_PI / 4) *
                rotation_x_matrix(M_PI / 2),
            Material(&wall_pat, Color(0.34, 0, 0.66),  // color
                     0.1,                              // ambient
                     0.5,                              // diffuse
                     0,                                // specular
                     0                                 // shininess
                     ));

  // glass_sphere
  Sphere s =
      glass_sphere(translation_matrix(0, 1, 0) * scaling_matrix(1, 1, 1));
  s.set_material(Material(
      NULL, Color(0, 0, 0),
      0.0,    // ambient. lower in transparent/reflective surfaces
      0.0,    // diffuse. lower in transparent/reflective surfaces
      1.0,    // specular
      300.0,  // shininess
      0.0f,   // reflectivity. 1.0 or 0.9 in glass/similar
      1.0f,   // transparency. 1.0 or 0.9 in transparent materials
      1.5f    // refractive index
      ));
  s.set_throws_shadow(false);
  // Add a light source
  PointLight light = PointLight(point(10, 10, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 1;
  unsigned int x = ratio * 128;
  unsigned int y = ratio * 80;
  Camera camera(x, y, M_PI / 3.75);
  camera.transform =
      view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{&floor, &left_mid_wall, &right_mid_wall, &s},
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
