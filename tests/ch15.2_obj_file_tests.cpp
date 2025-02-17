#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Ignore unrecognized lines
// p213
TEST(TestOBJ, ReadGibberish) {}

// Scenario: Vertex records
// p214
TEST(TestOBJ, ReadVertexRecords) {}
