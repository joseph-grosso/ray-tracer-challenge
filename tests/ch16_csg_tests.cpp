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

  CSG c = CSG("union", &s1, &s2);

  EXPECT_EQ(c.get_operation(), "union");
  EXPECT_EQ(c.get_left(), &s1);
  EXPECT_EQ(c.get_right(), &s2);
  EXPECT_EQ(s1.parent, &c);
  EXPECT_EQ(s2.parent, &c);
}
