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

// Scenario: Precomputing the reflection vector
// p143
TEST(TestReflection, ComputeReflectionVector) {
  Plane p = Plane();
  Ray r = Ray(point(0, 1, -1), vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  Intersection i = Intersection(std::sqrt(2), &p);

  Computation comps = i.prepare_computations(r, Intersections());

  EXPECT_EQ(comps.reflectv, vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
}

// Scenario: The reflected color for a nonreflective material
// p144
TEST(TestReflection, NonreflectiveMaterialColor) {
  World w = default_world();
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Material m = Material();
  m.ambient = 1;
  w.objects[1]->set_material(m);
  Intersection i = Intersection(1, w.objects[1]);

  Computation comps = i.prepare_computations(r, Intersections());
  Color c = w.reflected_color(comps);

  EXPECT_EQ(c, Color(0, 0, 0));
}

// Scenario: Strike a reflective surface
// p144
TEST(TestReflection, ReflectiveMaterialColor) {
  World w = default_world();
  Plane p = Plane(translation_matrix(0, -1, 0),
                  Material(Color(1, 1, 1),
                           0.1F,    // ambient
                           0.9F,    // diffuse
                           0.9F,    // specular
                           200.0F,  // shininess
                           0.5F     // reflectiveness - Non-default value
                           ));
  w.objects.push_back(&p);
  Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  w.objects[1]->set_material(Material());
  Intersection i = Intersection(std::sqrt(2), &p);

  Computation comps = i.prepare_computations(r, Intersections());
  Color col = w.reflected_color(comps);

  EXPECT_EQ(col, Color(0.19032, 0.2379, 0.14274));
}

// Scenario: shade_hit function with a reflective material
// p145
TEST(TestReflection, ShadeHitWithReflection) {
  World w = default_world();
  Plane p = Plane(translation_matrix(0, -1, 0),
                  Material(Color(1, 1, 1),
                           0.1F,    // ambient
                           0.9F,    // diffuse
                           0.9F,    // specular
                           200.0F,  // shininess
                           0.5F     // reflectiveness - Non-default value
                           ));
  w.objects.push_back(&p);
  Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  Intersection i = Intersection(std::sqrt(2), &p);

  Computation comps = i.prepare_computations(r, Intersections());
  Color col = w.shade_hit(comps);

  EXPECT_EQ(col, Color(0.87677, 0.92436, 0.82918));
}

// Scenario: color_at function with mutually reflective surfaces
// p146
TEST(TestReflection, ColorAtFuncExitsSuccessfully) {
  Material reflective_mat = Material();
  reflective_mat.reflective = 1.0F;

  Plane lower = Plane(translation_matrix(0, -1, 0), reflective_mat);
  Plane upper = Plane(translation_matrix(0, 1, 0), reflective_mat);
  World w = World(std::vector<Shape *>{&upper, &lower},
                  PointLight(point(0, 0, 0), Color(1, 1, 1)));
  Ray r = Ray(point(0, 0, 0), vector(0, 1, 0));

  auto start = std::chrono::high_resolution_clock::now();
  Color c = w.color_at(r);
  auto end = std::chrono::high_resolution_clock::now();

  double time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(start - end)
          .count();

  EXPECT_TRUE(time_span < 1.0);  // fix this value
}

// Scenario: The reflected color at the max recursive depth
// p147
TEST(TestReflection, LimitRecursion) {
  World w = default_world();
  Plane p = Plane(translation_matrix(0, -1, 0),
                  Material(Color(1, 1, 1),
                           0.1F,    // ambient
                           0.9F,    // diffuse
                           0.9F,    // specular
                           200.0F,  // shininess
                           0.5F     // reflectiveness - Non-default value
                           ));
  w.objects.push_back(&p);
  Ray r = Ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  Intersection i = Intersection(std::sqrt(2), &p);

  Computation comps = i.prepare_computations(r, Intersections());
  Color col = w.reflected_color(comps, 0);

  EXPECT_EQ(col, Color(0, 0, 0));
}

// Scenario: Transarency and Refractive Index for the default material
// p150
TEST(TestTransparencyAndRefraction, DefaultTranspAndRI) {
  Material m = Material();

  EXPECT_TRUE(equalByEpsilon(m.transparency, (float)0.0));
  EXPECT_TRUE(equalByEpsilon(m.refractive_index, (float)1.0));
}

// Scenario: A helper for producing a sphere with a glassy material
// p151
TEST(TestTransparencyAndRefraction, GlassSphereHelper) {
  Sphere m = glass_sphere();

  EXPECT_TRUE(equalByEpsilon(m.get_material().transparency, (float)1.0));
  EXPECT_TRUE(equalByEpsilon(m.get_material().refractive_index, (float)1.5));
}

// Scenario: Finding n1 and n2 at various intersections
// p152
TEST(TestTransparencyAndRefraction, FindingIntersections) {
  Sphere A = glass_sphere(scaling_matrix(2, 2, 2), 1.5);
  Sphere B = glass_sphere(translation_matrix(0, 0, -0.25), 2.0);
  Sphere C = glass_sphere(translation_matrix(0, 0, 0.25), 2.5);
  Ray r = Ray(point(0, 0, -4), vector(0, 0, 1));
  Intersections xs = Intersections(std::vector<Intersection>{
      Intersection(2, &A),
      Intersection(2.75, &B),
      Intersection(3.25, &C),
      Intersection(4.75, &B),
      Intersection(5.25, &C),
      Intersection(6, &A),
  });

  Computation c0 = xs[0].prepare_computations(r, xs);
  EXPECT_EQ(c0.n1, 1.0f);
  EXPECT_EQ(c0.n2, 1.5f);

  Computation c1 = xs[1].prepare_computations(r, xs);
  EXPECT_EQ(c1.n1, 1.5f);
  EXPECT_EQ(c1.n2, 2.0f);

  Computation c2 = xs[2].prepare_computations(r, xs);
  EXPECT_EQ(c2.n1, 2.0f);
  EXPECT_EQ(c2.n2, 2.5f);

  Computation c3 = xs[3].prepare_computations(r, xs);
  EXPECT_EQ(c3.n1, 2.5f);
  EXPECT_EQ(c3.n2, 2.5f);

  Computation c4 = xs[4].prepare_computations(r, xs);
  EXPECT_EQ(c4.n1, 2.5f);
  EXPECT_EQ(c4.n2, 1.5f);

  Computation c5 = xs[5].prepare_computations(r, xs);
  EXPECT_EQ(c5.n1, 1.5f);
  EXPECT_EQ(c5.n2, 1.0f);
}

// Scenario: The under point is offset below the surface
// p154
TEST(TestTransparencyAndRefraction, UnderPoint) {
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = glass_sphere(translation_matrix(0, 0, 1));
  Intersection i = Intersection(5, &s);
  Intersections xs = Intersections(std::vector<Intersection>{i});

  Computation comps = i.prepare_computations(r, xs);

  EXPECT_TRUE(comps.under_point.z > 0.001);
  EXPECT_TRUE(comps.point.z < comps.under_point.z);
}
