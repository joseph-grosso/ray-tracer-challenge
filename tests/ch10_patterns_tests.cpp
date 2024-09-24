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
    
}
