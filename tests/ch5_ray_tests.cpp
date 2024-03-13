#include <string>
#include <vector>
#include <iostream>
#include "tuple.h"
#include "matrix.h"
#include "transform.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
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
    Sphere s = Sphere();

    Intersection xs = r.intersect(s);

    EXPECT_EQ(xs.get_count(), 2);
    EXPECT_EQ(xs[0], 4.0);
    EXPECT_EQ(xs[1], 6.0);
}

// Scenario: A ray touches a sphere
// p60
TEST (TestRays, RayAndSphereTouch) {
    Ray r(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersection xs = r.intersect(s);

    EXPECT_EQ(xs.get_count(), 2);
    EXPECT_EQ(xs[0], 5.0);
    EXPECT_EQ(xs[1], 5.0);
}

// Scenario: A ray misses a sphere
// p60
TEST (TestRays, RayMissesSphere) {
    Ray r(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersection xs = r.intersect(s);

    EXPECT_EQ(xs.get_count(), 0);
}

// Scenario: A ray originates inside a sphere
// p60
TEST (TestRays, RayInsideSphere) {
    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersection xs = r.intersect(s);

    EXPECT_EQ(xs.get_count(), 2);
    EXPECT_EQ(xs[0], -1.0);
    EXPECT_EQ(xs[1], 1.0);
}

// Scenario: A sphere is behind a ray
// p60
TEST (TestRays, SphereBehindRay) {
    Ray r(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersection xs = r.intersect(s);

    EXPECT_EQ(xs.get_count(), 2);
    EXPECT_EQ(xs[0], -6.0);
    EXPECT_EQ(xs[1], -4.0);
}
