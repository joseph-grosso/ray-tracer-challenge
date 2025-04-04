#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "material.hpp"
#include "pattern.hpp"
#include "solid_pattern.hpp"
#include "sphere.hpp"
#include "stripe_pattern.hpp"
#include "transform.hpp"

// TODO: group all patterns into one hpp
#include "blend_pattern.hpp"
#include "checkers_pattern.hpp"
#include "conical_ring_pattern.hpp"
#include "gradient_pattern.hpp"
#include "radial_ring_pattern.hpp"

// Fixture: Set up the material and positions
// p128
class TestPatterns_Fixture : public testing::Test {
 protected:
  SolidPattern black = SolidPattern(Color(0, 0, 0));
  SolidPattern white = SolidPattern(Color(1, 1, 1));
};

// Scenario: Creating a stripe pattern
// p128
TEST_F(TestPatterns_Fixture, CreateStripePattern) {
  StripePattern p = StripePattern(&white, &black);

  EXPECT_EQ(p.get_a(), &white);
  EXPECT_EQ(p.get_b(), &black);
}

// Scenario: A stripe pattern is constant in y
// p129
TEST_F(TestPatterns_Fixture, PatternConstantInY) {
  StripePattern p = StripePattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 1, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 2, 0)), white.get_color());
}

// Scenario: A stripe pattern is constant in z
// p129
TEST_F(TestPatterns_Fixture, PatternConstantInZ) {
  StripePattern p = StripePattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 1)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 2)), white.get_color());
}

// Scenario: A stripe pattern alternates in x
// p129
TEST_F(TestPatterns_Fixture, PatternAlternatesInX) {
  StripePattern p = StripePattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0.9, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(1, 0, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(-0.1, 0, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(-1, 0, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(-1.1, 0, 0)), white.get_color());
}

// Scenario: Lighting with a pattern applied
// p129
TEST_F(TestPatterns_Fixture, LightingWithPattern) {
  Material m = Material();
  StripePattern pat = StripePattern(&white, &black);
  m.pattern = &pat;
  m.ambient = 1;
  m.diffuse = 0;
  m.specular = 0;
  Sphere s = Sphere();

  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

  Color c1 = m.lighting(&s, light, point(0.9, 0, 0), eyev, normalv, false);
  Color c2 = m.lighting(&s, light, point(1.1, 0, 0), eyev, normalv, false);

  EXPECT_EQ(c1, white.get_color());
  EXPECT_EQ(c2, black.get_color());
}

// Scenario: Stripes with an object transformation
// p131
TEST_F(TestPatterns_Fixture, StripesWithObjectTransform) {
  Sphere s = Sphere(scaling_matrix(2, 2, 2));
  StripePattern pattern = StripePattern(&white, &black);

  Color c = pattern.pattern_at_shape(&s, point(1.5, 0, 0));
  EXPECT_EQ(c, white.get_color());
}

// Scenario: Stripes with an pattern transformation
// p131
TEST_F(TestPatterns_Fixture, StripesWithPatternTransform) {
  Sphere s = Sphere();
  StripePattern pattern = StripePattern(&white, &black);
  pattern.set_transform(scaling_matrix(2, 2, 2));

  Color c = pattern.pattern_at_shape(&s, point(1.5, 0, 0));
  EXPECT_EQ(c, white.get_color());
}

// Scenario: Stripes with a pattern and an object transformation
// p131
TEST_F(TestPatterns_Fixture, StripesWithBothTransforms) {
  Sphere s = Sphere(scaling_matrix(2, 2, 2));
  StripePattern pattern = StripePattern(&white, &black);
  pattern.set_transform(translation_matrix(0.5, 0, 0));

  Color c = pattern.pattern_at_shape(&s, point(2.5, 0, 0));
  EXPECT_EQ(c, white.get_color());
}

// Abstract class for testing patterns class
class TestPattern : public Pattern {
 public:
  TestPattern(Matrix t = identity_matrix()) : Pattern(t){};
  Color pattern_at(Tuple p) { return Color(p.x(), p.y(), p.z()); };
};

// Scenario: The default pattern transformation
// p133
TEST(TestAbstractPattern, DefaultPatternTransform) {
  TestPattern p = TestPattern();

  EXPECT_EQ(p.get_transform(), identity_matrix());
}

// Scenario: Assigning a transformation
// p133
TEST(TestAbstractPattern, AssigningPatternTransform) {
  TestPattern p = TestPattern(translation_matrix(1, 2, 3));

  EXPECT_EQ(p.get_transform(), translation_matrix(1, 2, 3));
}

// Scenario: A pattern with an object transformation
// p134
TEST(TestAbstractPattern, PatternObjectTransform) {
  Sphere s = Sphere(scaling_matrix(2, 2, 2));
  TestPattern p = TestPattern();

  Color c = p.pattern_at_shape(&s, point(2, 3, 4));

  EXPECT_EQ(c, Color(1, 1.5, 2));
}

// Scenario: A pattern with an pattern transformation
// p134
TEST(TestAbstractPattern, PatternPatternTransform) {
  Sphere s = Sphere();
  TestPattern p = TestPattern(scaling_matrix(2, 2, 2));

  Color c = p.pattern_at_shape(&s, point(2, 3, 4));

  EXPECT_EQ(c, Color(1, 1.5, 2));
}

// Scenario: A pattern with both object and pattern transformations
// p134
TEST(TestAbstractPattern, PatternBothTransforms) {
  Sphere s = Sphere(scaling_matrix(2, 2, 2));
  TestPattern p = TestPattern(translation_matrix(0.5, 1, 1.5));

  Color c = p.pattern_at_shape(&s, point(2.5, 3, 3.5));

  EXPECT_EQ(c, Color(0.75, 0.5, 0.25));
}

// Scenario: A gradient linearly interpolates between colors
// p135
TEST_F(TestPatterns_Fixture, GradientPattern) {
  GradientPattern p = GradientPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
  EXPECT_EQ(p.pattern_at(point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
  EXPECT_EQ(p.pattern_at(point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

// Scenario: a CONICAL ring should extend in both x and z
// p136
TEST_F(TestPatterns_Fixture, ConicalRingsPattern) {
  ConicalRingPattern p = ConicalRingPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(1, 0, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 1)), black.get_color());
  // just outside sqrt(2) / 2
  EXPECT_EQ(p.pattern_at(point(0.708, 0, 0.708)), black.get_color());
}

// Scenario: Checkers should repeat in x
// p137
TEST_F(TestPatterns_Fixture, CheckersInX) {
  CheckersPattern p = CheckersPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0.99, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(1.01, 0, 0)), black.get_color());
}

// Scenario: Checkers should repeat in y
// p137
TEST_F(TestPatterns_Fixture, CheckersInY) {
  CheckersPattern p = CheckersPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0.99, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 1.01, 0)), black.get_color());
}

// Scenario: Checkers should repeat in z
// p137
TEST_F(TestPatterns_Fixture, CheckersInZ) {
  CheckersPattern p = CheckersPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 0.99)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 1.01)), black.get_color());
}

// Scenario: a RADIAL ring should extend in x, y, and z
// p138/pMe
TEST_F(TestPatterns_Fixture, RadialRingsPattern) {
  RadialRingPattern p = RadialRingPattern(&white, &black);

  EXPECT_EQ(p.pattern_at(point(0, 0, 0)), white.get_color());
  EXPECT_EQ(p.pattern_at(point(1, 0, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 0, 1)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(0, 1.1, 0)), black.get_color());
  EXPECT_EQ(p.pattern_at(point(1, 1, 1)), black.get_color());
  // just outside sqrt(2) / 2
  EXPECT_EQ(p.pattern_at(point(0.708, 0, 0.708)), black.get_color());
}

// Scenario: a solid color pattern should return the same color everywhere
// p139/pMe
TEST_F(TestPatterns_Fixture, SolidColorPattern) {
  EXPECT_EQ(white.get_color(), Color(1, 1, 1));
  EXPECT_EQ(white.pattern_at(point(0, 0, 0)), Color(1, 1, 1));
  EXPECT_EQ(white.pattern_at(point(1000, 100, 10)), Color(1, 1, 1));
  EXPECT_EQ(white.pattern_at(point(-150.0, 0.5, -11)), Color(1, 1, 1));
  EXPECT_EQ(black.get_color(), Color(0, 0, 0));
  EXPECT_EQ(black.pattern_at(point(0, 0, 0)), Color(0, 0, 0));
  EXPECT_EQ(black.pattern_at(point(10, 10, 10)), Color(0, 0, 0));
  EXPECT_EQ(black.pattern_at(point(-1500.0, 0.0001, 19)), Color(0, 0, 0));
}

// Scenario: a blend pattern should return a mix of the two subpatterns
// p139/pMe
TEST_F(TestPatterns_Fixture, BlendColorPattern) {
  BlendPattern bp = BlendPattern(&white, &black);

  EXPECT_EQ(bp.pattern_at(point(0, 0, 0)), Color(0.5, 0.5, 0.5));
}

// Scenario: a blend pattern should return a specified mix of the two
// subpatterns p139/pMe
TEST_F(TestPatterns_Fixture, BlendColorPatternByPercent) {
  BlendPattern bp = BlendPattern(&white, &black, 0.75);

  EXPECT_EQ(bp.pattern_at(point(0, 0, 0)), Color(0.75, 0.75, 0.75));
}
