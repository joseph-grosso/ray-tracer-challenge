#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "intersection.hpp"
#include "intersections.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "smooth_triangle.hpp"
#include "sphere.hpp"
#include "transform.hpp"
#include "tuple.hpp"

// Scenario: Creating and querying a ray
// p58
TEST(TestRays, QueryingRay) {
  Tuple origin = point(1, 2, 3);
  Tuple direction = vector(4, 5, 6);

  Ray r(origin, direction);

  EXPECT_EQ(r.get_origin(), origin);
  EXPECT_EQ(r.get_direction(), direction);
}

// Scenario: Finding the position along a ray
// p58
TEST(TestRays, PositionAlongRay) {
  Ray r(point(2, 3, 4), vector(1, 0, 0));

  EXPECT_EQ(r.position(0), point(2, 3, 4));
  EXPECT_EQ(r.position(1), point(3, 3, 4));
  EXPECT_EQ(r.position(-1), point(1, 3, 4));
  EXPECT_EQ(r.position(2.5), point(4.5, 3, 4));
}

// Scenario: Intersecting a sphere and a ray
// p59
TEST(TestRays, RayAndSphereIntersection) {
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();

  Intersections xs = s.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].t, 4.0);
  EXPECT_EQ(xs[1].t, 6.0);
}

// Scenario: A ray touches a sphere
// p60
TEST(TestRays, RayAndSphereTouch) {
  Ray r(point(0, 1, -5), vector(0, 0, 1));
  Sphere s = Sphere();

  Intersections xs = s.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].t, 5.0);
  EXPECT_EQ(xs[1].t, 5.0);
}

// Scenario: A ray misses a sphere
// p60
TEST(TestRays, RayMissesSphere) {
  Ray r(point(0, 2, -5), vector(0, 0, 1));
  Sphere s = Sphere();

  Intersections xs = s.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray originates inside a sphere
// p61
TEST(TestRays, RayInsideSphere) {
  Ray r(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();

  Intersections xs = s.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].t, -1.0);
  EXPECT_EQ(xs[1].t, 1.0);
}

// Scenario: A sphere is behind a ray
// p62
TEST(TestRays, SphereBehindRay) {
  Ray r(point(0, 0, 5), vector(0, 0, 1));
  Sphere s = Sphere();

  Intersections xs = s.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].t, -6.0);
  EXPECT_EQ(xs[1].t, -4.0);
}

// Scenario: An intersection encapsulates t and object
// p63
TEST(TestRays, IntersectionEncapsulatesTAndObject) {
  Sphere s = Sphere();
  Intersection i = Intersection(3.5, &s);

  EXPECT_EQ(i.t, 3.5);
  EXPECT_EQ(i.object, &s);
}

// Scenario: Aggregating intersections
// p64
TEST(TestRays, AggregatingIntersections) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(1, &s);
  Intersection i2 = Intersection(2, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].object, &s);
  EXPECT_EQ(xs[1].object, &s);

  // FTODO: Write up why this doesn't work and see if you can fix it
  // Sphere a = *xs[1].object
  // EXPECT_EQ(*xs[0].object, s);
  // EXPECT_EQ(*xs[1].object, s);
}

// Scenario: Get the hit when all intersections have positive t
// p65
TEST(TestRays, IdentifyIntersectionIfAllPositive) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(1, &s);
  Intersection i2 = Intersection(2, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});

  EXPECT_EQ(xs.hit(), i1);
}

// Scenario: Get the hit when some intersections have negative t
// p65
TEST(TestRays, IdentifyIntersectionIfSomeNegative) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-1, &s);
  Intersection i2 = Intersection(2, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});

  EXPECT_EQ(xs.hit(), i2);
}

// Scenario: Get the hit when all intersections have negative t
// p65
TEST(TestRays, IdentifyIntersectionIfAllNegative) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-1, &s);
  Intersection i2 = Intersection(-2, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});

  EXPECT_EQ(xs.hit().is_empty(), true);
}

// Scenario: The hit is always the lowest nonnegative intersection
// p66
TEST(TestRays, LowestNonNegIntersection) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(5, &s);
  Intersection i2 = Intersection(7, &s);
  Intersection i3 = Intersection(-3, &s);
  Intersection i4 = Intersection(2, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2, i3, i4});

  EXPECT_EQ(xs.hit(), i4);
}

// Scenario: Translating a ray
// p69
TEST(TestRays, TranslatingARay) {
  Ray r(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = translation_matrix(3, 4, 5);

  Ray r2 = r.transform(m);

  EXPECT_EQ(r2.get_origin(), point(4, 6, 8));
  EXPECT_EQ(r2.get_direction(), vector(0, 1, 0));
}

// Scenario: Scaling a ray
// p69
TEST(TestRays, ScalingARay) {
  Ray r(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = scaling_matrix(2, 3, 4);

  Ray r2 = r.transform(m);

  EXPECT_EQ(r2.get_origin(), point(2, 6, 12));
  EXPECT_EQ(r2.get_direction(), vector(0, 3, 0));
}

// Scenario: Intersecting a scaled sphere with a ray
// p69
TEST(TestRays, IntersectScaledSphere) {
  Sphere s = Sphere();
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  s.set_transform(scaling_matrix(2, 2, 2));
  Intersections xs = s.intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_EQ(xs[0].t, 3);
  EXPECT_EQ(xs[1].t, 7);
}

// Scenario: Intersecting a translated sphere with a ray
// p70
TEST(TestRays, IntersectTranslatedSphere) {
  Sphere s = Sphere();
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  s.set_transform(translation_matrix(5, 0, 0));
  Intersections xs = s.intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: Testing equality of spheres
// pMe
TEST(TestRays, TestSphereEquality) {
  EXPECT_EQ(Sphere(), Sphere());
  EXPECT_EQ(Sphere(translation_matrix(1, 2, 3), Material()),
            Sphere(translation_matrix(1.0, 2.0, 3.0), Material()));
  EXPECT_EQ(Sphere(Material()), Sphere(Material()));

  EXPECT_NE(Sphere(translation_matrix(1, 2, 3)), Sphere(Material()));
  EXPECT_NE(Sphere(), Sphere(Material(Color(10, 1, 1), 1, 1, 1, 1.0)));
  EXPECT_NE(Sphere(translation_matrix(1, 2, 3)), Sphere());
}

// ch15: intersections with triangles include u and v values
// Scenario: Regular intersection u and v values are NaN
// pMe
TEST(TestIntersections, TestIntersectNaNs) {
  Sphere s = Sphere();
  Intersection i = Intersection(10.0, &s);

  EXPECT_EQ(i.object, &s);
  EXPECT_TRUE(equalByEpsilon(i.t, 10.0));
  EXPECT_TRUE(std::isnan(i.u));
  EXPECT_TRUE(std::isnan(i.v));
}

// Scenario: Triangle intersection u and v values can be set
// p221
TEST(TestIntersections, TestTriangleIntersectUAndV) {
  SmoothTriangle s =
      SmoothTriangle(point(1, 0, 0), point(0, 1, 0), point(1, 1, 0),  // points
                     vector(1, 0, 0), vector(1, 0, 0), vector(1, 0, 0));
  Intersection i = Intersection(3.5, &s, 0.4, 0.2);

  EXPECT_EQ(i.object, &s);
  EXPECT_TRUE(equalByEpsilon(i.t, 3.5));
  EXPECT_TRUE(equalByEpsilon(i.u, 0.4));
  EXPECT_TRUE(equalByEpsilon(i.v, 0.2));
}
