#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.h"

// Fixture: Set up the material and positions
// p86
class TestShadows_Fixture : public testing::Test {
 protected:
  Material m = Material();
  Tuple position = point(0, 0, 0);
};

// Scenario: Lighting with the surface in shadow
// p110
TEST_F(TestShadows_Fixture, SurfaceInShadow) {
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = true;
  Sphere s = Sphere();

  Color result = m.lighting(&s, light, position, eyev, normalv, in_shadow);

  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

// Scenario: There is no shadow when nothing is collinear with point and light
// p111
TEST(TestShadows, NoShadowAtPoint) {
  World w = default_world();
  Tuple p = point(0, 10, 0);

  EXPECT_EQ(w.is_shadowed(p), false);
}

// Scenario: There shadow when an object is between the point and light
// p112
TEST(TestShadows, ShadowAtPoint) {
  World w = default_world();
  Tuple p = point(10, -10, 10);

  EXPECT_EQ(w.is_shadowed(p), true);
}

// Scenario: There is no shadow when an object is behind the light
// p112
TEST(TestShadows, NoShadowAtPointBehindLight) {
  World w = default_world();
  Tuple p = point(-20, 20, -20);

  EXPECT_EQ(w.is_shadowed(p), false);
}

// Scenario: There is no shadow when an object is behind the point
// p112
TEST(TestShadows, NoShadowAtPointBetweenLightAndObject) {
  World w = default_world();
  Tuple p = point(-2, 2, -2);

  EXPECT_EQ(w.is_shadowed(p), false);
}

// Scenario: shade_hit() is given an intersection in shadow
// p114
TEST(TestShadows, ShadeHitAtIntersection) {
  Sphere s1, s2;
  s2.set_transform(translation_matrix(0, 0, 10));

  std::vector<PointLight> light = {
      PointLight(point(0, 0, -10), Color(1, 1, 1))};
  std::vector<Shape *> objects = {&s1, &s2};
  World w(objects, light);

  Ray r(point(0, 0, 5), vector(0, 0, 1));
  Intersection i(4, &s2);

  Computation comps = i.prepare_computations(r);
  Color c = w.shade_hit(comps);

  EXPECT_EQ(c, Color(0.1, 0.1, 0.1));
}

// Scenario: The hit should offset the point
// p115
TEST(TestShadows, HitOffsetAtPoint) {
  float EPSILON = 0.00001;
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s;
  s.set_transform(translation_matrix(0, 0, 1));

  Intersection i(5, &s);
  Computation comps = i.prepare_computations(r);

  EXPECT_TRUE(comps.over_point.z < -EPSILON / 2);
  EXPECT_TRUE(comps.point.z > comps.over_point.z);
}