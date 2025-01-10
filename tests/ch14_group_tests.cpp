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
