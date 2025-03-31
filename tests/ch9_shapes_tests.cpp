#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "gtest/gtest.h"
#include "plane.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "transform.hpp"

class TestShape : public Shape {
 public:
  // default ray
  Ray saved_ray = Ray(point(0, 0, 0), vector(1, 0, 0));
  Intersections local_intersect(Ray r) {
    this->saved_ray = r;
    return Intersections();
  };
  Tuple local_normal_at(Tuple p, Intersection i) {
    return vector(p.x(), p.y(), p.z());
  };
};

// Chapter 9: Refactoring Shapes
// Scenario: The default transformation
// p119
TEST(TestAbstractShape, DefaultTransform) {
  TestShape s = TestShape();

  EXPECT_EQ(s.get_transform(), identity_matrix());
}

// Scenario: Assigning a transformation
// p119
TEST(TestAbstractShape, AssignedTransform) {
  TestShape s = TestShape();
  s.set_transform(translation_matrix(2, 3, 4));
  EXPECT_EQ(s.get_transform(), translation_matrix(2, 3, 4));
}

// Scenario: The default material
// p119
TEST(TestAbstractShape, DefaultMaterial) {
  Material m = Material();
  TestShape s = TestShape();
  EXPECT_EQ(m, s.get_material());
}

// Scenario: Assigning a material
// p119
TEST(TestAbstractShape, AssigningMaterial) {
  Material m = Material();
  TestShape s = TestShape();

  m.ambient = 1;
  s.set_material(m);

  EXPECT_EQ(m, s.get_material());
}

// Scenario: Intersecting a scaled shape with a ray
// p120
TEST(TestAbstractShape, IntersectScaledShape) {
  TestShape s = TestShape();
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  s.set_transform(scaling_matrix(2, 2, 2));
  Intersections xs = s.intersect(r);

  EXPECT_EQ(s.saved_ray.get_origin(), point(0, 0, -2.5));
  EXPECT_EQ(s.saved_ray.get_direction(), vector(0, 0, 0.5));
}

// Scenario: Intersecting a translated shape with a ray
// p120
TEST(TestAbstractShape, IntersectTranslatedShape) {
  TestShape s = TestShape();
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  s.set_transform(translation_matrix(5, 0, 0));
  Intersections xs = s.intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: Computing the normal of a sphere on a translated shape
// p121
// TODO: Delete original tests as they are no longer needed (refactor on p121)
TEST(TestAbstractShape, NormalOfTranslatedSphere) {
  TestShape s = TestShape();
  s.set_transform(translation_matrix(0, 1, 0));
  Tuple n = s.normal_at(point(0, 1.70711, -0.70711));

  EXPECT_EQ(n, vector(0, 0.70711, -0.70711));
}

// Scenario: Computing the normal on a transformed shape
// p121
// TODO: Delete original tests as they are no longer needed (refactor on p121)
TEST(TestAbstractShape, NormalOfTransformedSphere) {
  TestShape s = TestShape();
  s.set_transform(scaling_matrix(1.0, 0.5f, 1.0) * rotation_z_matrix(M_PI / 5));

  Tuple n = s.normal_at(point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));

  EXPECT_EQ(n, vector(0, 0.97014, -0.24254));
}

// Planes tests

// Scenario: The normal of a plane is constant everywhere
// p122
TEST(TestPlanes, NormalOfPlane) {
  Plane p = Plane();

  Tuple n1 = p.local_normal_at(point(0, 0, 0));
  Tuple n2 = p.local_normal_at(point(10, 0, -10));
  Tuple n3 = p.local_normal_at(point(-5, 0, 150));

  EXPECT_EQ(n1, vector(0, 1, 0));
  EXPECT_EQ(n2, vector(0, 1, 0));
  EXPECT_EQ(n3, vector(0, 1, 0));
}

// Scenario: Intersect with a ray parallel to the plane
// p123
TEST(TestPlanes, IntersectParallelRay) {
  Plane p = Plane();

  Ray r = Ray(point(0, 10, 0), vector(0, 0, 1));
  Intersections xs = p.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: Intersect with a coplanar ray
// p123
TEST(TestPlanes, IntersectCoplanarRay) {
  Plane p = Plane();

  Ray r = Ray(point(0, 10, 0), vector(0, 0, 1));
  Intersections xs = p.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray intersecting a plane from above
// p123
TEST(TestPlanes, IntersectRayAbove) {
  Plane p = Plane();

  Ray r = Ray(point(0, 1, 0), vector(0, -1, 0));
  Intersections xs = p.local_intersect(r);

  EXPECT_EQ(xs.count, 1);
  EXPECT_EQ(xs[0].t, 1);
  EXPECT_EQ(xs[0].object, &p);
}

// Scenario: A ray intersecting a plane from below
// p123
TEST(TestPlanes, IntersectRayBelow) {
  Plane p = Plane();

  Ray r = Ray(point(0, -1, 0), vector(0, 1, 0));
  Intersections xs = p.local_intersect(r);

  EXPECT_EQ(xs.count, 1);
  EXPECT_EQ(xs[0].t, 1);
  EXPECT_EQ(xs[0].object, &p);
}

// ch14: Groups
// Scenario: All shapes have a parent attribute
// p195
TEST(TestAbstractShape, ParentAttribute) {
  TestShape s = TestShape();

  EXPECT_EQ(s.parent, nullptr);
}
