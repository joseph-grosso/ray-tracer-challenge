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
  SolidPattern brown_ed = SolidPattern(Color(0.29, 0.07, 0.05));
  SolidPattern green_world = SolidPattern(Color(0.53, 0.61, 0.20));
  SolidPattern blue__world = SolidPattern(Color(0.33, 0.50, 0.79));
  SolidPattern gray_w = SolidPattern(Color(0.33, 0.29, 0.31));

  // complex patterns
  StripePattern stripe_pat_1 = StripePattern(
      &red_l, &red_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(M_PI / 3));
  StripePattern stripe_pat_2 = StripePattern(
      &blue_l, &blue_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(-M_PI / 3));
  PerlinPattern wall_pat =
      PerlinPattern(&brown_l, &brown_d, 0, scaling_matrix(0.1, 0.1, 0.1));
  PerlinPattern table_pat =
      PerlinPattern(&brown_ed, &brown_d, 1, scaling_matrix(0.1, 0.1, 0.1));
  PerlinPattern globe_pat = PerlinPattern(&green_world, &blue__world, 2,
                                          scaling_matrix(0.2, 0.2, 0.2));
  PerlinPattern map_pat = PerlinPattern(&green_world, &blue__world, 4,
                                        scaling_matrix(0.4, 0.4, 0.4));

  // common material
  Material wood =
      Material(&table_pat, Color(0, 0, 0), 0.1, 0.9, 0.9, 300.0, 0.15);

  // Define the objects
  // roof and floor
  Cube roof_and_floor =
      Cube(scaling_matrix(100, 15, 100) * translation_matrix(0, 1, 0),
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
  float table_offset = 2.7;
  Cube table_top =
      Cube(translation_matrix(0, 2, 1.5) * scaling_matrix(3, 0.2, 3) *
               translation_matrix(0, 1, 0),
           wood);
  // table legs
  Cube table_leg_front_left = Cube(
      translation_matrix(-table_offset, 0, -table_offset) *  // move front left
          translation_matrix(0, 0, 1.5) * scaling_matrix(0.3, 2, 0.3),
      wood);
  Cube table_leg_front_right = Cube(
      translation_matrix(table_offset, 0, -table_offset) *  // move front right
          translation_matrix(0, 0, 1.5) * scaling_matrix(0.3, 2, 0.3),
      wood);
  Cube table_leg_back_left = Cube(
      translation_matrix(-table_offset, 0, table_offset) *  // move back left
          translation_matrix(0, 0, 1.5) * scaling_matrix(0.3, 2, 0.3),
      wood);
  Cube table_leg_back_right = Cube(
      translation_matrix(table_offset, 0, table_offset) *  // move back right
          translation_matrix(0, 0, 1.5) * scaling_matrix(0.3, 2, 0.3),
      wood);

  // globe
  Sphere globe =
      Sphere(translation_matrix(0, 3.8, 2.5),
             Material(&globe_pat, Color(0, 0, 0), 0.3, 0.7, 0.2, 10.0));

  // globe stand
  Cube globe_stand =
      Cube(translation_matrix(0, 2.7, 2.5) * scaling_matrix(0.4, 0.3, 0.4),
           Material(&gray_w, Color(0, 0, 0), 0.1, 0.9, 0.9, 200.0, 0.1));

  // map
  Cube map =
      Cube(translation_matrix(-7.9, 4.5, 2) * scaling_matrix(1.0, 1.5, 3.0),
           Material(&map_pat, Color(0, 0, 0), 0.1, 0.9, 0.1, 30.0));

  // Add a light source
  PointLight light = PointLight(point(-0.5, 10, -4), Color(1, 1, 1));

  // Create camera
  int ratio = 2;
  unsigned int x = ratio * 70;
  unsigned int y = ratio * 70;
  Camera camera(x, y, M_PI / 2.1);
  camera.transform =
      view_transform(point(2, 5, -4), point(-0.1, 2.6, 0), vector(0, 1, 0));

  // Create world
  World w(
      std::vector<Shape *>{// walls and roof
                           &walls, &roof_and_floor,
                           // mirror
                           &mirror,
                           // globe vars
                           &globe, &globe_stand,
                           // table top
                           &table_top,
                           // leg vars
                           &table_leg_front_left, &table_leg_front_right,
                           &table_leg_back_left, &table_leg_back_right,
                           // map var
                           &map},
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
