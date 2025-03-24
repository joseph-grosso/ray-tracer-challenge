#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "triangle.hpp"
#include "smooth_triangle.hpp"

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


// Fixture: Set up smooth triangle
// p220
class TestSmoothTriangle : public testing::Test {
  protected:
    Tuple p1 = point(0, 1, 0);
    Tuple p2 = point(-1, 0, 0);
    Tuple p3 = point(1, 0, 0);
    Tuple n1 = vector(0, 1, 0);
    Tuple n2 = vector(-1, 0, 0);
    Tuple n3 = vector(1, 0, 0);
    SmoothTriangle tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
};
 
 // Scenario: Constructing a smooth triangle
 // p221
 TEST_F(TestSmoothTriangle, ConstructingSmoothTriangle) { 
  EXPECT_EQ(tri.p1, p1);
  EXPECT_EQ(tri.p2, p2);
  EXPECT_EQ(tri.p3, p3);
  EXPECT_EQ(tri.n1, n1);
  EXPECT_EQ(tri.n2, n2);
  EXPECT_EQ(tri.n3, n3);
}
  
// Scenario: An intersection with a smooth triangle stores u/v
// p222
TEST_F(TestSmoothTriangle, IntersectHasUAndV) { 
  Ray r = Ray(point(-0.2, 0.3, -2), vector(0, 0, 1));
  Intersections xs = tri.local_intersect(r);

  EXPECT_TRUE(equalByEpsilon(xs[0].u, 0.45));
  EXPECT_TRUE(equalByEpsilon(xs[0].v, 0.25));  
}

// Scenario: A smooth triangle uses u/v to interpolate the normal
// p222
TEST_F(TestSmoothTriangle, NormalInterpolation) { 
  Ray r = Ray(point(-0.2, 0.3, -2), vector(0, 0, 1));
  Intersection i = Intersection(1, &tri, 0.45, 0.25);
  Tuple n = tri.normal_at(point(0, 0, 0), i);

  EXPECT_EQ(n, vector(-0.5547, 0.83205, 0));
}

// Scenario: preparing the normal on a smooth triangle
// p222
TEST_F(TestSmoothTriangle, SmoothTriangleComputations) { 
  Intersection i = Intersection(1, &tri, 0.45, 0.25);
  Ray r = Ray(point(-0.2, 0.3, -2), vector(0, 0, 1));
  Intersections xs = Intersections(std::vector<Intersection> {i});

  Computation comps = i.prepare_computations(r, xs);

  EXPECT_EQ(comps.normalv, vector(-0.5547, 0.83205, 0));
}
