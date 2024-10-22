// TODO: Is this required?
#include <gmock/gmock.h>
#include <math.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Reflectivity for the default material
// p143
TEST(TestReflection, DefaultReflectivity) {
  Material m = Material();

  EXPECT_EQ(m.reflective, (float)0.0);
}

// // Scenario: Precomputing the reflection vector
// // p143
// TEST(TestReflection, ComputeReflectionVector) {
//   Plane p = Plane();
//   Ray r = Ray(point(0, 1, -1), vector(0, -std::sqrt(2) / 2, std::sqrt(2) /
//   2)); Intersection i = Intersection(std::sqrt(2), &p);

//   Computation comps = i.prepare_computations(r);

//   EXPECT_EQ(comps.reflectv, vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
// }

// // Scenario: The reflected color for a nonreflective material
// // p144
// TEST(TestReflection, NonreflectiveMaterialColor) {
//   World w = default_world();
//   Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
//   w.objects[1]->set_material(Material());

//   EXPECT_EQ(m.get_reflective(), (float)0.0);
// }

// // Scenario: Strike a reflective surface
// // p144
// TEST(TestReflection, ReflectiveMaterialColor) {
//   World w = default_world();
//   Plane p = Plane(translation_matrix(0, -1, 0),
//                   Material(Color(1, 1, 1),
//                            0.1F,    // ambient
//                            0.9F,    // diffuse
//                            0.9F,    // specular
//                            200.0F,  // shininess
//                            0.5F     // reflectiveness - Non-default value
//                            ));
//   w.objects.push_back(&p);
//   Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) /
//   2)); w.objects[1]->set_material(Material()); Intersection i =
//   Intersection(std::sqrt(2), &p);

//   Computation comps = i.prepare_computations(r);
//   Color col = w.reflected_color(comps);

//   EXPECT_EQ(col, Color(0.19032, 0.2379, 0.14274));
// }

// // Scenario: shade_hit function with a reflective material
// // p145
// TEST(TestReflection, ShadeHitWithReflection) {
//   World w = default_world();
//   Plane p = Plane(translation_matrix(0, -1, 0),
//                   Material(Color(1, 1, 1),
//                            0.1F,    // ambient
//                            0.9F,    // diffuse
//                            0.9F,    // specular
//                            200.0F,  // shininess
//                            0.5F     // reflectiveness - Non-default value
//                            ));
//   w.objects.push_back(&p);
//   Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) /
//   2)); Intersection i = Intersection(std::sqrt(2), &p);

//   Computation comps = i.prepare_computations(r);
//   Color col = w.shade_hit(comps);

//   EXPECT_EQ(col, Color(0.87677, 0.92436, 0.82918));
// }

// // Scenario: color_at function with mutually reflective surfaces
// // p146
// TEST(TestReflection, ColorAtFuncExitsSuccessfully) {
//   Material reflective_mat = Material();
//   reflective_mat.reflectiveness = 1.0F;

//   Plane lower = Plane(translation_matrix(0, -1, 0), reflective_mat);
//   Plane upper = Plane(translation_matrix(0, -1, 0), reflective_mat);
//   World w = World(std::vector<Shape *>{upper, lower},
//                   PointLight(point(0, 0, 0), Color(1, 1, 1)));
//   Ray r = Ray(point(0, 0, 0), vector(0, 1, 0));

//   auto start = std::chrono::high_resolution_clock::now();
//   Color c = w.color_at(r);
//   auto end = std::chrono::high_resolution_clock::now();

//   EXPECT_EQ(end - start, 1.0F);  // fix this value
// }

// // Scenario: The reflected color at the max recursive depth
// // p147
// TEST(TestReflection, LimitRecursion) {
//   World w = default_world();
//   Plane p = Plane(translation_matrix(0, -1, 0),
//                   Material(Color(1, 1, 1),
//                            0.1F,    // ambient
//                            0.9F,    // diffuse
//                            0.9F,    // specular
//                            200.0F,  // shininess
//                            0.5F     // reflectiveness - Non-default value
//                            ));
//   w.objects.push_back(&p);
//   Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) /
//   2)); Intersection i = Intersection(std::sqrt(2), &p);

//   Computation comps = i.prepare_computations(r);
//   Color col = w.reflected_color(comps, 0);

//   EXPECT_EQ(col, Color(0, 0, 0));
// }