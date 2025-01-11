#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Creating a new group
// p195
TEST(TestGroups, CreateNewGroup) {
  Group g = Group();

  EXPECT_EQ(g.get_transform(), identity_matrix(4));
  EXPECT_EQ(g.get_count(), 0);
  EXPECT_EQ(g.is_empty(), true);
}

class TestShape : public Shape {
 public:
  // default ray
  Ray saved_ray = Ray(point(0, 0, 0), vector(1, 0, 0));
  Intersections local_intersect(Ray r) {
    this->saved_ray = r;
    return Intersections();
  };
  Tuple local_normal_at(Tuple p) { return vector(p.x, p.y, p.z); };
};

// Scenario: Adding a child to a group
// p195
TEST(TestGroups, AddChildToGroup) {
  Group g = Group();
  TestShape s = TestShape();

  g.add_child(&s);

  EXPECT_EQ(g.get_transform(), identity_matrix(4));
  EXPECT_EQ(g.is_empty(), false);
  EXPECT_EQ(&g, s.parent);
}

// Scenario: Intersecting a ray with an empty group
// p196
TEST(TestGroups, IntersectingEmptyGroup) {
  Group g = Group();
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));

  Intersections xs = g.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: Intersecting a ray with a nonempty group
// p196
TEST(TestGroups, IntersectingNonemptyGroup) {
  Group g = Group();
  Sphere s1 = Sphere();
  Sphere s2 = Sphere(translation_matrix(0, 0, -3));
  Sphere s3 = Sphere(translation_matrix(5, 0, 0));

  g.add_child(&s1);
  g.add_child(&s2);
  g.add_child(&s3);

  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  Intersections xs = g.local_intersect(r);

  EXPECT_EQ(xs.count, 4);
  EXPECT_EQ(xs[0].object, &s2);
  EXPECT_EQ(xs[1].object, &s2);
  EXPECT_EQ(xs[2].object, &s1);
  EXPECT_EQ(xs[3].object, &s1);
}

// Scenario: Intersecting a transformed group
// p197
TEST(TestGroups, IntersectingTransformedGroup) {
  Group g = Group(scaling_matrix(2, 2, 2));
  Sphere s1 = Sphere(translation_matrix(5, 0, 0));

  g.add_child(&s1);

  Ray r = Ray(point(10, 0, -10), vector(0, 0, 1));

  Intersections xs = g.intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].object, &s1);
  EXPECT_EQ(xs[1].object, &s1);
}

// Scenario: Converting a point from world to object space
// p198
TEST(TestGroups, GroupPointToObjectSpace) {
  Group g1 = Group(rotation_y_matrix(M_PI_2));
  Group g2 = Group(scaling_matrix(2, 2, 2));
  Sphere s = Sphere(translation_matrix(5, 0, 0));

  g1.add_child(&g2);
  g2.add_child(&s);

  Tuple p = s.world_to_object(point(-2, 0, -10));

  EXPECT_EQ(p, point(0, 0, -1));
}

// Scenario: Converting a normal from object to world space
// p198
TEST(TestGroups, NormalToWorldSpace) {
  Group g1 = Group(rotation_y_matrix(M_PI_2));
  Group g2 = Group(scaling_matrix(1, 2, 3));
  Sphere s = Sphere(translation_matrix(5, 0, 0));

  g1.add_child(&g2);
  g2.add_child(&s);

  Tuple n = s.normal_to_world(vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

  EXPECT_EQ(n, vector(0.2857, 0.4286, -0.8571));
}

// Scenario: Converting a normal from object to world space
// p198
TEST(TestGroups, NormalToWorldSpace) {
  Group g1 = Group(rotation_y_matrix(M_PI_2));
  Group g2 = Group(scaling_matrix(1, 2, 3));
  Sphere s = Sphere(translation_matrix(5, 0, 0));

  g1.add_child(&g2);
  g2.add_child(&s);

  Tuple n = s.normal_to_world(vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

  EXPECT_EQ(n, vector(0.2857, 0.4286, -0.8571));
}
