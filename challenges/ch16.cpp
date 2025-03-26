#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// The last big thing
int main() {
  // Colors
  Color mirror_green = Color(69.0 / 256.0, 76.0 / 256.0, 68.0 / 256.0);
  Color steel = Color(0.50, 0.56, 0.62);
  SolidPattern floor_dark =
      SolidPattern(Color(43.0 / 256.0, 43.0 / 256.0, 52.0 / 256.0));
  SolidPattern floor_light =
      SolidPattern(Color(83.0 / 256.0, 86.0 / 256.0, 90.0 / 256.0));

  Pattern *room_floor_pat = new PerlinPattern(&floor_dark, &floor_light, 26,
                                              scaling_matrix(0.5, 0.5, 0.5),
                                              true  // fade_together
  );
  Material steel_mat = Material(NULL, steel, 0.1, 0.9, 0.9, 500, 1.0F);
  Material slight_green_reflection =
      Material(NULL, mirror_green, 0.9, 0.1, 0.9, 1000, 1.0F);
  // initialize group
  Cube *central_mirror =
      new Cube(scaling_matrix(0.5, 2.3, 0.5), slight_green_reflection);
  Cube *mirror_cap =
      new Cube(translation_matrix(0, 2.3, 0) * scaling_matrix(0.55, 0.05, 0.55),
               steel_mat);
  Cube *mirror_base = new Cube(
      translation_matrix(0, 0, 0) * scaling_matrix(0.55, 0.3, 0.55), steel_mat);
  Group *central_mirror_group =
      new Group(identity_matrix(),
                std::vector<Shape *>{central_mirror, mirror_cap, mirror_base});

  Material floor_mat = Material(room_floor_pat, Color(-1, -1, -1),  // color
                                0.2,                                // ambient
                                0.9,                                // diffuse
                                1.4,                                // specular
                                10                                  // shininess
  );
  Plane *floor = new Plane(translation_matrix(0, 0, 0), floor_mat);
  Tuple camera_point = point(0, 1.1, -3);
  Tuple light_point = camera_point;

  // Add a light source
  PointLight light = PointLight(light_point, Color(1, 1, 1));

  // Create camera
  int ratio = 20;
  unsigned int x = ratio * 10;
  unsigned int y = ratio * 10;
  Camera camera(x, y, M_PI / 3);
  camera.transform =
      view_transform(camera_point, point(0, 1.1, 0), vector(0, 1, 0));

  // Create world
  World w(std::vector<Shape *>{central_mirror_group, floor}, light);

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
