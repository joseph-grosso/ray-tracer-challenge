#include <cmath>
#include <iostream>

#include "ray_tracer.hpp"

int main() {
  // Create and position floor sphere
  Sphere floor_sphere(scaling_matrix(10, 0.01, 10) * translation_matrix(0, -1, 0));
  Material floor_mat(NULL, Color(1, 0.9, 0.9), 0.1, 0.9, 0, 200.0);
  floor_sphere.set_material(floor_mat);

  // Create left wall
  Sphere left_wall(scaling_matrix(10, 0.01, 10) * rotation_z_matrix(M_PI / 2) *
                   translation_matrix(0, 0, 5));
  left_wall.set_material(floor_mat);

  // Create right wall
  Sphere right_wall(scaling_matrix(10, 0.01, 10) * rotation_z_matrix(M_PI / 2) *
                    translation_matrix(0, 0, -5));
  right_wall.set_material(floor_mat);

  // Middle sphere
  Sphere middle(translation_matrix(-0.5, 1, 0.5));
  Material middle_mat(NULL, Color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0);
  middle.set_material(middle_mat);

  // Right sphere
  Sphere right(scaling_matrix(0.5, 0.5, 0.5) * translation_matrix(1.5, 0.5, -0.5));
  Material right_mat(NULL, Color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200.0);
  right.set_material(right_mat);

  // Left sphere
  Sphere left(scaling_matrix(0.33, 0.33, 0.33) * translation_matrix(-1.5, 0.33, -0.75));
  Material left_mat(NULL, Color(1, 0.2, 1), 0.1, 0.7, 0.3, 200.0);
  left.set_material(left_mat);

  // Create world with objects and light
  PointLight light(point(-10, 10, -10), Color(1, 1, 1));
  World w(std::vector<Shape *>{&floor_sphere, &left_wall, &right_wall, &middle, &right, &left}, light);

  // Set up camera
  Camera camera(800, 600, M_PI / 3);
  camera.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0)));

  // Render
  std::cout << "Rendering scene..." << std::endl;
  Canvas image = camera.render(w);

  // Export to both PNG and PPM
  std::cout << "Exporting to PNG..." << std::endl;
  image.write_to_png("ch_png_demo.png");

  std::cout << "Exporting to PPM..." << std::endl;
  image.write_to_ppm("ch_png_demo.ppm");

  std::cout << "✓ Scene rendered successfully!" << std::endl;
  std::cout << "✓ PNG file: ch_png_demo.png" << std::endl;
  std::cout << "✓ PPM file: ch_png_demo.ppm" << std::endl;

  return 0;
}
