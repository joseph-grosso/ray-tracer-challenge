#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "csg.hpp"
#include "cube.hpp"
#include "gtest/gtest.h"
#include "sphere.hpp"

// Scenario: CSG is created with an operation and two shapes
// p230
TEST(TestCSG, CreateNewCSG) {
  Sphere s1 = Sphere();
  Cube s2 = Cube();

  CSG c = CSG(CSGOperation::UNION, &s1, &s2);

  EXPECT_EQ(c.get_operation(), CSGOperation::UNION);
  EXPECT_EQ(c.get_left(), &s1);
  EXPECT_EQ(c.get_right(), &s2);
  EXPECT_EQ(s1.parent, &c);
  EXPECT_EQ(s2.parent, &c);
}

class TestCSGOps : public testing::TestWithParam<
                       std::tuple<CSGOperation, bool, bool, bool, bool>> {};

// Scenario: Evaluating the rule for a CSG operation
// p230
TEST_P(TestCSGOps, TestIntersectAllowed) {
  auto [op, lhit, inl, inr, expected] = GetParam();
  auto s1 = Sphere();
  auto s2 = Sphere();
  CSG c = CSG(op, &s1, &s2);

  bool actual = c.intersection_allowed(lhit, inl, inr);

  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    TestCSGRules, TestCSGOps,
    ::testing::Values(
        // UNION tests
        std::make_tuple(CSGOperation::UNION, true, true, true, false),
        std::make_tuple(CSGOperation::UNION, true, true, false, true),
        std::make_tuple(CSGOperation::UNION, true, false, true, false),
        std::make_tuple(CSGOperation::UNION, true, false, false, true),
        std::make_tuple(CSGOperation::UNION, false, true, true, false),
        std::make_tuple(CSGOperation::UNION, false, true, false, false),
        std::make_tuple(CSGOperation::UNION, false, false, true, true),
        std::make_tuple(CSGOperation::UNION, false, false, false, true),
        // INTERSECTION
        std::make_tuple(CSGOperation::INTERSECTION, true, true, true, true),
        std::make_tuple(CSGOperation::INTERSECTION, true, true, false, false),
        std::make_tuple(CSGOperation::INTERSECTION, true, false, true, true),
        std::make_tuple(CSGOperation::INTERSECTION, true, false, false, false),
        std::make_tuple(CSGOperation::INTERSECTION, false, true, true, true),
        std::make_tuple(CSGOperation::INTERSECTION, false, true, false, true),
        std::make_tuple(CSGOperation::INTERSECTION, false, false, true, false),
        std::make_tuple(CSGOperation::INTERSECTION, false, false, false, false),
        // DIFFERENCE
        std::make_tuple(CSGOperation::DIFFERENCE, true, true, true, false),
        std::make_tuple(CSGOperation::DIFFERENCE, true, true, false, true),
        std::make_tuple(CSGOperation::DIFFERENCE, true, false, true, false),
        std::make_tuple(CSGOperation::DIFFERENCE, true, false, false, true),
        std::make_tuple(CSGOperation::DIFFERENCE, false, true, true, true),
        std::make_tuple(CSGOperation::DIFFERENCE, false, true, false, true),
        std::make_tuple(CSGOperation::DIFFERENCE, false, false, true, false),
        std::make_tuple(CSGOperation::DIFFERENCE, false, false, false, false)));
