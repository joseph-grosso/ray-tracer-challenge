#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Cowboy hat in the desert
int main() {
  // initialize group
  OBJParser o;
  o.parse_obj_file("challenges/input/mccreescetchfab.obj");  // edited obj file

  Group *cowboy_supplies = o.obj_to_group();
  Color leather = Color(100.0 / 256.0, 67.0 / 256.0, 46.0 / 256.0);
  Material leather_mat = Material(NULL, leather,  // color
                                  0.1,            // ambient
                                  0.9,            // diffuse
                                  0.0,            // specular
                                  500             // shininess
  );
  SolidPattern sand_1 = SolidPattern(Color(0.8509, 0.7647, 0.6627));
  SolidPattern sand_2 = SolidPattern(Color(0.7490, 0.6078, 0.4784));

  Pattern *desert_floor_pat =
      new PerlinPattern(&sand_1, &sand_2, 26, scaling_matrix(0.12, 0.12, 0.12),
                        true  // fade_together
      );

  Material desert_floor_mat =
      Material(desert_floor_pat, Color(-1, -1, -1),  // color
               0.2,                                  // ambient
               0.9,                                  // diffuse
               1.4,                                  // specular
               10                                    // shininess
      );
  Plane *floor = new Plane(translation_matrix(0, 0.65, 0), desert_floor_mat);
  cowboy_supplies->set_all_materials(leather_mat);
  Tuple camera_point = point(-3, 3, 3);
  Tuple light_point = point(0, 45, 100);

  // Add a light source
  PointLight light = PointLight(light_point, Color(1, 1, 1));

  // Create camera
  int ratio = 10;
  unsigned int x = ratio * 10;
  unsigned int y = ratio * 5;
  Camera camera(x, y, M_PI / 7.5);
  camera.transform =
      view_transform(camera_point, point(0, 0.75, -0.1), vector(0, 1.5, 0));

  // Create world
  World w(std::vector<Shape *>{cowboy_supplies, floor}, light);

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
