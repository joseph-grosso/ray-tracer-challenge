#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// cube room
int main() {
  SolidPattern red_l = SolidPattern(Color(0.886, 0.247, 0.266));
  SolidPattern red_d = SolidPattern(Color(0.443, 0.121, 0.133));
  SolidPattern blue_l = SolidPattern(Color(0.678, 0.874, 1));
  SolidPattern blue_d = SolidPattern(Color(0.450, 0.584, 0.666));
  StripePattern stripe_pat_1 = StripePattern(
      &red_l, &red_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(M_PI / 3));
  StripePattern stripe_pat_2 = StripePattern(
      &blue_l, &blue_d,
      scaling_matrix(0.25, 0.25, 0.25) * rotation_y_matrix(-M_PI / 3));
  CheckersPattern combined_pat =
      CheckersPattern(&stripe_pat_2, &stripe_pat_1,
                      scaling_matrix(5, 5, 5) * rotation_y_matrix(-M_PI / 8));

  // Define the objects
  // Floor Plane
  Plane *floor = new Plane(rotation_x_matrix(M_PI / 2),
                           Material(&combined_pat, Color(1, 0.9, 0.9),  // color
                                    0.1,  // ambient
                                    0.5,  // diffuse
                                    0,    // specular
                                    0     // shininess
                                    ));

  // initialize group
  OBJParser o;
  o.parse_obj_file("challenges/input/teapot-low_modified.obj");

  Group *teapot = o.obj_to_group();

  // Add a light source
  PointLight light = PointLight(point(6, -19, 17), Color(1, 1, 1));

  // Create camera
  int ratio = 2;
  unsigned int x = ratio * 10;
  unsigned int y = ratio * 7;
  Camera camera(x, y, M_PI / 2.3);
  camera.transform =
      view_transform(point(5, -19, 17), point(3, 0, 6), vector(0, 0, 1));

  // Create world
  World w(std::vector<Shape *>{teapot, floor}, light);

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
