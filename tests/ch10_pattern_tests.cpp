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
// p126
TEST_F (TestPatterns_Fixture, CreateStripePattern) {
    StripePattern p = StripePattern(white, black);

    EXPECT_EQ(p.a, white);
    EXPECT_EQ(p.b, black);
}