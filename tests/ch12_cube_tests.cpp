// TODO: Is this required?
#include <gmock/gmock.h>
#include <math.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "cube.hpp"
#include "gtest/gtest.h"

class TestCubeIntersection
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, float, float>> {};

// Scenario: A ray intersects a cube
// p168
TEST_P(TestCubeIntersection, RayIntersectsCube) {
  auto [origin, direction, t1, t2] = GetParam();

  Cube c = Cube();
  Ray r = Ray(origin, direction);

  Intersections xs = c.local_intersect(r);

  ASSERT_EQ(xs.count, 2);
  ASSERT_EQ(xs[0].t, t1);
  ASSERT_EQ(xs[1].t, t2);
}

INSTANTIATE_TEST_SUITE_P(
    TestIntersections, TestCubeIntersection,
    ::testing::Values(
        std::make_tuple(point(5, 0.5, 0), vector(-1, 0, 0), 4.0, 6.0),
        std::make_tuple(point(-5, 0.5, 0), vector(1, 0, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, 5, 0), vector(0, -1, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, -5, 0), vector(0, 1, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, 0, 5), vector(0, 0, -1), 4.0, 6.0),
        std::make_tuple(point(0.5, 0, -5), vector(0, 0, 1), 4.0, 6.0),
        std::make_tuple(point(0, 0.5, 0), vector(0, 0, 1), -1, 1)));

class TestCubeMiss : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

// Scenario: A ray misses a cube
// p172
TEST_P(TestCubeMiss, RayMissesCube) {
  auto [origin, direction] = GetParam();

  Cube c = Cube();
  Ray r = Ray(origin, direction);

  Intersections xs = c.local_intersect(r);

  ASSERT_EQ(xs.count, 0);
}

INSTANTIATE_TEST_SUITE_P(
    TestMisses, TestCubeMiss,
    ::testing::Values(
        std::make_tuple(point(-2, 0, 0), vector(0.2673, 0.5345, 0.8018)),
        std::make_tuple(point(0, -2, 0), vector(0.8018, 0.2673, 0.5345)),
        std::make_tuple(point(0, 0, -2), vector(0.5345, 0.8018, 0.2673)),
        std::make_tuple(point(2, 0, 2), vector(0, 0, -1)),
        std::make_tuple(point(0, 2, 2), vector(0, -1, 0)),
        std::make_tuple(point(2, 2, 0), vector(-1, 0, 0))));

class TestCubeNormal : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {
};

// Scenario: The normal on the surface of a cube
// p173
TEST_P(TestCubeNormal, CubeSurfaceNormal) {
  auto [point_, expected_normal] = GetParam();

  Cube c = Cube();

  Tuple actual_normal = c.local_normal_at(point_);

  ASSERT_EQ(actual_normal, expected_normal);
}

// Scenario: The normal on the surface of a cube - other possible function
// p173 - repeat
TEST_P(TestCubeNormal, CubeSurfaceNormalAlternative) {
  auto [point_, expected_normal] = GetParam();

  Cube c = Cube();

  Tuple actual_normal = c.local_normal_at(point_.x(), point_.y(), point_.z());

  ASSERT_EQ(actual_normal, expected_normal);
}

INSTANTIATE_TEST_SUITE_P(
    TestNormal, TestCubeNormal,
    ::testing::Values(std::make_tuple(point(1.0, 0.5, -0.8), vector(1, 0, 0)),
                      std::make_tuple(point(-1.0, 0.2, 0.9), vector(-1, 0, 0)),
                      std::make_tuple(point(-0.4, 1.0, -0.1), vector(0, 1, 0)),
                      std::make_tuple(point(0.3, -1.0, -0.7), vector(0, -1, 0)),
                      std::make_tuple(point(-0.6, 0.3, 1.0), vector(0, 0, 1)),
                      std::make_tuple(point(0.4, 0.4, -1.0), vector(0, 0, -1)),
                      std::make_tuple(point(1, 1, 1), vector(1, 0, 0)),
                      std::make_tuple(point(-1, -1, -1), vector(-1, 0, 0))));
