#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Constructing a triangle
// p208
TEST(TestTriangles, CreateNewTriangle) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);

  Triangle t = Triangle(p1, p2, p3);

  EXPECT_EQ(t.get_transform(), identity_matrix(4));
  EXPECT_EQ(t.p1, p1);
  EXPECT_EQ(t.p2, p2);
  EXPECT_EQ(t.p3, p3);
  EXPECT_EQ(t.e1, vector(-1, -1, 0));
  EXPECT_EQ(t.e2, vector(1, -1, 0));
  EXPECT_EQ(t.normal, vector(0, 0, -1));
}

// Scenario: Finding the noraml on a triangle
// p209
TEST(TestTriangles, TriangleNormal) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);

  EXPECT_EQ(t.normal, t.local_normal_at(point(0, 0.5, 0)));
  EXPECT_EQ(t.normal, t.local_normal_at(point(-0.5, 0.75, 0)));
  EXPECT_EQ(t.normal, t.local_normal_at(point(0.5, 0.25, 0)));
}

// Scenario: Intersecting a ray parallel to the triangle
// p210
TEST(TestTriangles, TriangleParallelRay) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);
  Ray r = Ray(point(0, -1, -2), vector(0, 1, 0));

  Intersections xs = t.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray misses the p1-p3 edge
// p211
TEST(TestTriangles, RayMissesTriangleEdge1) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);
  Ray r = Ray(point(1, 1, -2), vector(0, 0, 1));

  Intersections xs = t.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray misses the p1-p2 edge
// p211
TEST(TestTriangles, RayMissesTriangleEdge2) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);
  Ray r = Ray(point(-1, 1, -2), vector(0, 0, 1));

  Intersections xs = t.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray misses the p2-p3 edge
// p211
TEST(TestTriangles, RayMissesTriangleEdge3) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);
  Ray r = Ray(point(0, -1, -2), vector(0, 0, 1));

  Intersections xs = t.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray strikes the triangle
// p211
TEST(TestTriangles, RayHitsTriangle) {
  Tuple p1 = point(0, 1, 0);
  Tuple p2 = point(-1, 0, 0);
  Tuple p3 = point(1, 0, 0);
  Triangle t = Triangle(p1, p2, p3);
  Ray r = Ray(point(0, 0.5, -2), vector(0, 0, 1));

  Intersections xs = t.local_intersect(r);

  EXPECT_EQ(xs.count, 1);
  EXPECT_TRUE(equalByEpsilon(xs[0].t, 2));
}
