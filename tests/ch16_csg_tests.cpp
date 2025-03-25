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
#include "transform.hpp"

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

class TestCSGHitFiltering
    : public testing::TestWithParam<std::tuple<CSGOperation, int, int>> {};

// Scenario: Filtering a list of intersections
// p234
TEST_P(TestCSGHitFiltering, TestIntersectFilter) {
  auto [op, x0, x1] = GetParam();
  auto s1 = Sphere();
  auto s2 = Cube();
  CSG c = CSG(op, &s1, &s2);
  Intersections xs = Intersections(
      std::vector<Intersection>{Intersection(1, &s1), Intersection(2, &s2),
                                Intersection(3, &s1), Intersection(4, &s2)});

  auto result = c.filter_intersections(xs);

  EXPECT_EQ(result.count, 2);
  EXPECT_EQ(result[0], xs[x0]);
  EXPECT_EQ(result[1], xs[x1]);
}

INSTANTIATE_TEST_SUITE_P(
    TestCSGHits, TestCSGHitFiltering,
    ::testing::Values(std::make_tuple(CSGOperation::UNION, 0, 3),
                      std::make_tuple(CSGOperation::INTERSECTION, 1, 2),
                      std::make_tuple(CSGOperation::DIFFERENCE, 0, 1)));

// TODO: add in tests for nested CSG and group objects testing "includes"
// overrides

// Scenario: A ray misses a CSG object
// p236
TEST(TESTCSG, TESTCSGRayMiss) {
  auto c = CSG(CSGOperation::UNION, new Sphere(), new Cube());
  auto r = Ray(point(0, 2, -5), vector(0, 0, 1));

  auto xs = c.local_intersect(r);

  EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray hits a CSG object
// p236
TEST(TESTCSG, TESTCSGRayHit) {
  auto s1 = Sphere();
  auto s2 = Sphere(translation_matrix(0, 0, 0.5));
  auto c = CSG(CSGOperation::UNION, &s1, &s2);
  auto r = Ray(point(0, 0, -5), vector(0, 0, 1));

  auto xs = c.local_intersect(r);

  EXPECT_EQ(xs.count, 2);
  EXPECT_TRUE(equalByEpsilon(xs[0].t, 4));
  EXPECT_EQ(xs[0].object, &s1);
  EXPECT_TRUE(equalByEpsilon(xs[1].t, 6.5));
  EXPECT_EQ(xs[1].object, &s2);
}
