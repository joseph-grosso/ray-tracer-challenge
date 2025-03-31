#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Group experimentation
int main() {
  SolidPattern brown_d = SolidPattern(Color(0.35, 0.15, 0.02));
  SolidPattern brown_ed = SolidPattern(Color(0.29, 0.07, 0.05));
  // complex patterns
  PerlinPattern table_pat =
      PerlinPattern(&brown_ed, &brown_d, 1, scaling_matrix(0.3, 0.3, 0.3));

  // common material
  Material wood = wood_material(&table_pat);
  Cylinder *cyl_x = new Cylinder(identity_matrix(), -3, 3, true, Material());
  Cylinder *cyl_y =
      new Cylinder(rotation_z_matrix(M_PI / 2), -3, 3, true, Material());
  Cylinder *cyl_z =
      new Cylinder(rotation_x_matrix(M_PI / 2), -3, 3, true, Material());

  Sphere *s = new Sphere(scaling_matrix(1.5, 1.5, 1.5));
  Group *parent = new Group(std::vector<Shape *>{cyl_x, cyl_y, cyl_z, s});
  parent->set_all_materials(wood);

  //   for (int i=0; i < 1; i++) {
  //     child = new Group(rotation_y_matrix(i * M_PI / 3), std::vector<Shape*>
  //     {g_main}); parent->add_child(child);
  //   };

  Tuple camera_point = point(4, 4, 4);
  Tuple light_point = camera_point;

  // Add a light source
  PointLight light = PointLight(light_point, Color(1, 1, 1));

  // Create camera
  int ratio = 20;
  unsigned int x = ratio * 10;
  unsigned int y = ratio * 10;
  Camera camera(x, y, M_PI / 3);
  camera.set_transform(
      view_transform(camera_point, point(0, 0, 0), vector(0, 1, 0)));

  // Create world
  //   World w(std::vector<Shape *>{cyl_x, cyl_y, cyl_z, s}, light);
  World w(std::vector<Shape *>{parent}, light);

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
