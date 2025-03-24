#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: CSG is created with an operation and two shapes
// p230
TEST(TestCSG, CreateNewGroup) {
  Group g = Group();

  EXPECT_EQ(g.get_transform(), identity_matrix(4));
  EXPECT_EQ(g.get_count(), 0);
  EXPECT_EQ(g.is_empty(), true);
}
