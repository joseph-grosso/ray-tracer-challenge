#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "ray_tracer.hpp"

using namespace std::chrono;

// All of the objects combined
int main() {
  // base patterns
  SolidPattern off_white = SolidPattern(Color(1.0, 1.0, 1.0));
  SolidPattern off_black = SolidPattern(Color(0.1, 0.1, 0.1));

  CheckersPattern floor_pat =
      CheckersPattern(&off_white, &off_black, scaling_matrix(0.7, 0.7, 0.7));

  // Define the objects
  // Floor Plane
  Plane *floor = new Plane(identity_matrix(),
                           Material(&floor_pat, Color(-1, -1, -1),  // color
                                    0.1,                            // ambient
                                    0.5,                            // diffuse
                                    0,                              // specular
                                    0                               // shininess
                                    ));

  // size matrix
  Matrix size_fix = scaling_matrix(0.45, 0.45, 0.45);
  Matrix orientation_fix = rotation_z_matrix(-M_PI / 2);

  // Objects:
  // Sphere
  Sphere *s =
      new Sphere(translation_matrix(0.7, 1, -1.7) * size_fix * orientation_fix,
                 Material(Color(1, 0, 0)));
  // Cube
  Cube *c =
      new Cube(translation_matrix(0.7, 1, -0.6) * size_fix * orientation_fix,
               Material(Color(0, 0, 1)));
  // Cylinder
  Cylinder *cyl =
      new Cylinder(translation_matrix(0.7, 1, 0.6) * size_fix * orientation_fix,
                   -1, 1, true, Material(Color(0, 1, 0)));
  // Cone
  Cone *cone =
      new Cone(translation_matrix(0.7, 1, 1.7) * scaling_matrix(2, 1, 1) *
                   size_fix * orientation_fix * translation_matrix(0, 0.5, 0),
               -1, 0, true, (Color(1, 1, 0)));
  // Group
  SolidPattern brown_d = SolidPattern(Color(0.35, 0.15, 0.02));
  SolidPattern brown_ed = SolidPattern(Color(0.29, 0.07, 0.05));
  PerlinPattern table_pat =
      PerlinPattern(&brown_ed, &brown_d, 1, scaling_matrix(0.1, 0.1, 0.1));

  // common material
  Material wood = wood_material(&table_pat);
  Cylinder *cyl_x = new Cylinder(identity_matrix(), -3, 3, true, Material());
  Cylinder *cyl_y =
      new Cylinder(rotation_z_matrix(M_PI / 2), -3, 3, true, Material());
  Cylinder *cyl_z =
      new Cylinder(rotation_x_matrix(M_PI / 2), -3, 3, true, Material());

  Sphere *sphere_middle = new Sphere(scaling_matrix(1.5, 1.5, 1.5));
  Group *wooden_group =
      new Group(std::vector<Shape *>{cyl_x, cyl_y, cyl_z, sphere_middle});
  wooden_group->set_all_materials(wood);
  wooden_group->set_transform(translation_matrix(-0.6, 1, 0) *
                              scaling_matrix(0.9 / 6.0, 0.9 / 6.0, 0.9 / 6.0) *
                              rotation_x_matrix(-M_PI / 9) *
                              rotation_z_matrix(-M_PI / 9) *
                              rotation_y_matrix(-M_PI / 9));
  // Triangle (group/triangle?)
  OBJParser parser = OBJParser();
  parser.parse_obj_file("challenges/input/changed_LP_heart_OBJ.obj");
  Group *heart = parser.obj_to_group();
  heart->set_transform(translation_matrix(-0.6, 1, 1.15) * orientation_fix *
                       scaling_matrix(1.0 / 65.0, 1.0 / 65.0, 1.0 / 65.0));
  // CSG
  float cyl_scaling = 0.55;
  Cylinder *cyl_x_csg =
      new Cylinder(scaling_matrix(cyl_scaling, cyl_scaling, cyl_scaling), -3, 3,
                   true, Material(Color(0, 1, 0)));
  Cylinder *cyl_y_csg =
      new Cylinder(rotation_z_matrix(M_PI / 2) *
                       scaling_matrix(cyl_scaling, cyl_scaling, cyl_scaling),
                   -3, 3, true, Material(Color(0, 1, 0)));
  Cylinder *cyl_z_csg =
      new Cylinder(rotation_x_matrix(M_PI / 2) *
                       scaling_matrix(cyl_scaling, cyl_scaling, cyl_scaling),
                   -3, 3, true, Material(Color(0, 1, 0)));
  Sphere *s_csg =
      new Sphere(scaling_matrix(1.42, 1.42, 1.42), Material(Color(0, 0, 1)));
  Cube *c_csg = new Cube(identity_matrix(), Material(Color(1, 0, 0)));

  CSG *union_1 = new CSG(CSGOperation::UNION, cyl_x_csg, cyl_y_csg);
  CSG *union_2 = new CSG(CSGOperation::UNION, union_1, cyl_z_csg);
  CSG *intersect = new CSG(CSGOperation::INTERSECTION, s_csg, c_csg);
  CSG *diff =
      new CSG(CSGOperation::DIFFERENCE, intersect, union_2,
              translation_matrix(-0.6, 1.2, -1.2) *
                  rotation_x_matrix(M_PI / 9) * rotation_z_matrix(M_PI / 5) *
                  rotation_y_matrix(-M_PI / 9) * size_fix);

  // Add a light source
  PointLight light = PointLight(point(3, 10, -3), Color(1, 1, 1));

  // Create camera
  int ratio = 15;
  unsigned int x = ratio * 100;
  unsigned int y = ratio * 70;
  Camera camera(x, y, M_PI / 10.5);
  camera.set_transform(
      view_transform(point(0, 16, 0), point(0, 0, 0), vector(1, 0, 0)));

  // Create world
  World w(
      std::vector<Shape *>{floor, s, c, cyl, cone, heart, wooden_group, diff},
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
