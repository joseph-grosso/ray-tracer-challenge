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

class TestMiss : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

// Scenario: A ray misses a cylinder
// p178
TEST_P(TestMiss, RayMisses) {
  Cylinder cyl = Cylinder();
  auto [origin, direction] = GetParam();
  direction = direction.normalize();
  Ray r = Ray(origin, direction);

  Intersections xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

INSTANTIATE_TEST_SUITE_P(
    TestCylinder, TestMiss,
    ::testing::Values(std::make_tuple(point(1, 0, 0), vector(0, 1, 0)),
                      std::make_tuple(point(0, 0, 0), vector(0, 1, 0)),
                      std::make_tuple(point(0, 0, -5), vector(1, 1, 1))));

class TestStrike
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, float, float>> {};

// Scenario: A ray strikes a cylinder
// p180
TEST_P(TestStrike, RayHits) {
  Cylinder cyl = Cylinder();
  auto [origin, direction, t0, t1] = GetParam();
  direction = direction.normalize();
  Ray r = Ray(origin, direction);

  Intersections xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_TRUE(equalByEpsilon(xs[0].t, t0));
  EXPECT_TRUE(equalByEpsilon(xs[1].t, t1));
}

INSTANTIATE_TEST_SUITE_P(
    TestCylinder, TestStrike,
    ::testing::Values(std::make_tuple(point(1, 0, -5), vector(0, 0, 1), 5, 5),
                      std::make_tuple(point(0, 0, -5), vector(0, 0, 1), 4, 6),
                      std::make_tuple(point(0.5, 0, -5), vector(0.1, 1, 1),
                                      6.80798, 7.08872)));

class TestNormalVector
    : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

// Scenario: Normal vector on a cylinder
// p181
TEST_P(TestNormalVector, NormalOfCylinder) {
  Cylinder cyl = Cylinder();
  auto [point_, normal] = GetParam();

  Tuple n = cyl.local_normal_at(point_);

  EXPECT_EQ(n, normal);
}

INSTANTIATE_TEST_SUITE_P(
    TestCylinder, TestNormalVector,
    ::testing::Values(std::make_tuple(point(1, 0, 0), vector(1, 0, 0)),
                      std::make_tuple(point(0, 5, -1), vector(0, 0, -1)),
                      std::make_tuple(point(0, -2, 1), vector(0, 0, 1)),
                      std::make_tuple(point(-1, 1, 0), vector(-1, 0, 0))));

// Scenario: The default minimum and maximum for a cylinder
// p182
TEST(TestCylinderCaps, DefaultMinAndMax) {
  Cylinder cyl = Cylinder();

  EXPECT_EQ(cyl.get_minimum(), -std::numeric_limits<float>::infinity());
  EXPECT_EQ(cyl.get_maximum(), std::numeric_limits<float>::infinity());
}

class TestConstrainedCylinder
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, float>> {};

// Scenario: Intersecting constrained cylinder
// p183
TEST_P(TestConstrainedCylinder, IntersectConstrainedCylinder) {
  Cylinder cyl = Cylinder(identity_matrix(4), 1, 2);
  auto [point_, direction, count] = GetParam();
  direction = direction.normalize();
  Ray r = Ray(point_, direction);

  Intersections xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.count, count);
}

INSTANTIATE_TEST_SUITE_P(
    TestCylinder, TestConstrainedCylinder,
    ::testing::Values(std::make_tuple(point(0, 1.5, 0), vector(0.1, 1, 0), 0),
                      std::make_tuple(point(0, 3, -5), vector(0, 0, 1), 0),
                      std::make_tuple(point(0, 0, -5), vector(0, 0, 1), 0),
                      std::make_tuple(point(0, 2, -5), vector(0, 0, 1), 0),
                      std::make_tuple(point(0, 1, -5), vector(0, 0, 1), 0),
                      std::make_tuple(point(0, 1.5, -2), vector(0, 0, 1), 2)));

// Scenario: The default closed value for a cylinder
// p185
TEST(TestCylinderCaps, DefaultNoCaps) {
  Cylinder cyl = Cylinder();

  EXPECT_FALSE(cyl.closed);
}

class TestCappedCylinder
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, float>> {};

// Scenario: Intersecting constrained, capped cylinder
// p185
TEST_P(TestCappedCylinder, IntersectCappedCylinder) {
  Cylinder cyl = Cylinder(identity_matrix(4), 1, 2, true);
  auto [point_, direction, count] = GetParam();
  direction = direction.normalize();
  Ray r = Ray(point_, direction);

  Intersections xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.count, count);
}

INSTANTIATE_TEST_SUITE_P(
    TestCylinder, TestCappedCylinder,
    ::testing::Values(std::make_tuple(point(0, 3, 0), vector(0, -1, 0), 2),
                      std::make_tuple(point(0, 3, -2), vector(0, -1, 2), 2),
                      std::make_tuple(point(0, 4, -2), vector(0, -1, 1), 2),
                      std::make_tuple(point(0, 0, -2), vector(0, 1, 2), 2),
                      std::make_tuple(point(0, -1, -2), vector(0, 1, 1), 2)));
