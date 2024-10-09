#include "ray_tracer.h"
#include "gtest/gtest.h"
#include <math.h>
#include <gmock/gmock.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>


// Fixture: Set up the material and positions
// p86
class TestPatterns_Fixture : public testing::Test {
    protected:
        Color black = Color(0, 0, 0);
        Color white = Color(1, 1, 1);
};

// Scenario: Creating a stripe pattern
// p128
TEST_F (TestPatterns_Fixture, CreateStripePattern) {
    StripePattern p = StripePattern(white, black);

    EXPECT_EQ(p.get_a(), white);
    EXPECT_EQ(p.get_b(), black);
}

// Scenario: A stripe pattern is constant in y
// p129
TEST_F (TestPatterns_Fixture, PatternConstantInY) {
    StripePattern p = StripePattern(white, black);

    EXPECT_EQ(p.stripe_at(point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(point(0, 1, 0)), white);
    EXPECT_EQ(p.stripe_at(point(0, 2, 0)), white);
}

// Scenario: A stripe pattern is constant in z
// p129
TEST_F (TestPatterns_Fixture, PatternConstantInZ) {
    StripePattern p = StripePattern(white, black);

    EXPECT_EQ(p.stripe_at(point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(point(0, 0, 1)), white);
    EXPECT_EQ(p.stripe_at(point(0, 0, 2)), white);
}

// Scenario: A stripe pattern alternates in x
// p129
TEST_F (TestPatterns_Fixture, PatternAlternatesInX) {
    StripePattern p = StripePattern(white, black);

    EXPECT_EQ(p.stripe_at(point(0, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(point(0.9, 0, 0)), white);
    EXPECT_EQ(p.stripe_at(point(1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(point(-0.1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(point(-1, 0, 0)), black);
    EXPECT_EQ(p.stripe_at(point(-1.1, 0, 0)), white);
}

// Scenario: Lighting with a pattern applied
// p129
TEST_F (TestPatterns_Fixture, LightingWithPattern) {
    Material m = Material();
    StripePattern pat = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    m.pattern = &pat;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    PointLight light = PointLight(point(0, 0, -10), Color(1, 1, 1));

    Color c1 = m.lighting(light, point(0.9, 0, 0), eyev, normalv, false);
    Color c2 = m.lighting(light, point(1.1, 0, 0), eyev, normalv, false);

    EXPECT_EQ(c1, white);
    EXPECT_EQ(c2, black);
}

// Scenario: Stripes with an object transformation
// p131
TEST_F (TestPatterns_Fixture, StripesWithObjectTransform) {
    Sphere s = Sphere(scaling_matrix(2, 2, 2));
    StripePattern pattern = StripePattern(white, black);

    Color c = pattern.stripe_at_object(&s, point(1.5, 0, 0));
    EXPECT_EQ(c, white);
   
}

// Scenario: Stripes with an pattern transformation
// p131
TEST_F (TestPatterns_Fixture, StripesWithPatternTransform) {
    Sphere s = Sphere();
    StripePattern pattern = StripePattern(white, black);
    pattern.set_transform(scaling_matrix(2, 2, 2));

    Color c = pattern.stripe_at_object(&s, point(1.5, 0, 0));
    EXPECT_EQ(c, white);
}

// Scenario: Stripes with a pattern and an object transformation
// p131
TEST_F (TestPatterns_Fixture, StripesWithBothTransforms) {
    Sphere s = Sphere(scaling_matrix(2, 2, 2));
    StripePattern pattern = StripePattern(white, black);
    pattern.set_transform(translation_matrix(0.5, 0, 0));

    Color c = pattern.stripe_at_object(&s, point(2.5, 0, 0));
    EXPECT_EQ(c, white);
}
