#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// Glass ball with air interior - small test example fresnel
int main() {
  // base patterns
  SolidPattern off_white = SolidPattern(Color(0.9, 0.9, 0.9));
  SolidPattern off_black = SolidPattern(Color(0.1, 0.1, 0.1));

  CheckersPattern floor_pat =
      CheckersPattern(&off_white, &off_black, scaling_matrix(1.8, 1.8, 1.8));

  // Define the objects
  // Floor Plane
  Plane floor = Plane(identity_matrix(4),
                      Material(&floor_pat, Color(1, 0.9, 0.9),  // color
                               0.1,                             // ambient
                               0.5,                             // diffuse
                               0,                               // specular
                               0                                // shininess
                               ));

  // glass_sphere
  Sphere s1 = glass_sphere(translation_matrix(0, 12, 0));

  // air bubble
  Sphere s2 =
      Sphere(translation_matrix(0, 12, 0) * scaling_matrix(0.5, 0.5, 0.5));
  s2.set_material(Material(
      NULL, Color(1, 0, 0),
      0.0,   // ambient. lower in transparent/reflective surfaces
      0.0,   // diffuse. lower in transparent/reflective surfaces
      0.0,   // specular
      0.0,   // shininess
      0.0f,  // reflectivity. 1.0 or 0.9 in glass/similar
      1.0f,  // transparency. 1.0 or 0.9 in transparent materials
      1.0f   // refractive index. Fresnel effect
      ));
  s1.set_throws_shadow(false);
  s2.set_throws_shadow(false);

  // Add a light source
  PointLight light = PointLight(point(10, 10, -10), Color(1, 1, 1));

  // Create camera
  int ratio = 2;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 100;
  Camera camera(x, y, M_PI / 4.5);
  camera.transform =
      view_transform(point(0, 16, 0), point(0, 0, 0), vector(1, 0, 0));

  // Create world
  World w(std::vector<Shape *>{&floor, &s1, &s2}, light);

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
