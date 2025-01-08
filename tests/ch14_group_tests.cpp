#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Creating a new group
// p195
TEST(TestGroups, CreateNewGroup) {
  Group g = Group();

  EXPECT_EQ(g.get_transform(), identity_matrix(4));
  EXPECT_EQ(g.get_count(), 0);
}
