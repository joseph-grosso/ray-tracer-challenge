#include <string>
#include <vector>
#include <iostream>
#include "tuple.h"
#include "matrix.h"
#include "transform.h"
#include "ray.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>
#include <cmath>


// Scenario: Creating and querying a ray
// p58
TEST (TestRays, QueryingRay) {
    Tuple origin = point(1, 2, 3);
    Tuple direction = vector(4, 5, 6);

    Ray r(origin, direction);

    EXPECT_EQ(r.get_origin(), origin);
    EXPECT_EQ(r.get_direction(), direction);
}

// Scenario: Finding the position along a ray
// p58
TEST (TestRays, PositionAlongRay) {
    Ray r(point(2, 3, 4), vector(1, 0, 0));

    EXPECT_EQ(r.position(0), point(2, 3, 4));
    EXPECT_EQ(r.position(1), point(3, 3, 4));
    EXPECT_EQ(r.position(-1), point(1, 3, 4));
    EXPECT_EQ(r.position(2.5), point(4.5, 3, 4));
}

// Scenario: Intersecting a sphere and a ray
// p59
TEST (TestRays, RayAndSphereIntersection) {
    Ray r(point(0, 0, -5), vector(0, 0, 1));
}