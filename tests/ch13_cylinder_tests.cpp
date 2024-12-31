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
