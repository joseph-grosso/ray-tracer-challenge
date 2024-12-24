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

class TestCube
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, float, float>> {};

// Scenario: A ray intersects a cube
// p168
TEST_P(TestCube, RayIntersectsCube) {
  auto [origin, direction, t1, t2] = GetParam();

  Cube c = Cube();
  Ray r = Ray(origin, direction);

  Intersections xs = c.local_intersect(r);

  ASSERT_EQ(xs.count, 2);
  ASSERT_EQ(xs[0].t, t1);
  ASSERT_EQ(xs[1].t, t2);
}

INSTANTIATE_TEST_SUITE_P(
    TestIntersections, TestCube,
    ::testing::Values(
        std::make_tuple(point(5, 0.5, 0), vector(-1, 0, 0), 4.0, 6.0),
        std::make_tuple(point(-5, 0.5, 0), vector(1, 0, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, 5, 0), vector(0, -1, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, -5, 0), vector(0, 1, 0), 4.0, 6.0),
        std::make_tuple(point(0.5, 0, 5), vector(0, 0, -1), 4.0, 6.0),
        std::make_tuple(point(0.5, 0, -5), vector(0, 0, 1), 4.0, 6.0),
        std::make_tuple(point(0, 0.5, 0), vector(0, 0, 1), -1, 1)));