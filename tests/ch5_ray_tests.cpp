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

    Intersections xs = intersect(s, r);

    EXPECT_EQ(xs.count, 2);
    EXPECT_EQ(xs[0].t, 4.0);
    EXPECT_EQ(xs[1].t, 6.0);
}

// Scenario: A ray touches a sphere
// p60
TEST (TestRays, RayAndSphereTouch) {
    Ray r(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersections xs = intersect(s, r);

    EXPECT_EQ(xs.count, 2);
    EXPECT_EQ(xs[0].t, 5.0);
    EXPECT_EQ(xs[1].t, 5.0);
}

// Scenario: A ray misses a sphere
// p60
TEST (TestRays, RayMissesSphere) {
    Ray r(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersections xs = intersect(s, r);

    EXPECT_EQ(xs.count, 0);
}

// Scenario: A ray originates inside a sphere
// p61
TEST (TestRays, RayInsideSphere) {
    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersections xs = intersect(s, r);

    EXPECT_EQ(xs.count, 2);
    EXPECT_EQ(xs[0].t, -1.0);
    EXPECT_EQ(xs[1].t, 1.0);
}

// Scenario: A sphere is behind a ray
// p62
TEST (TestRays, SphereBehindRay) {
    Ray r(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = Sphere();

    Intersections xs = intersect(s, r);

    EXPECT_EQ(xs.count, 2);
    EXPECT_EQ(xs[0].t, -6.0);
    EXPECT_EQ(xs[1].t, -4.0);
}

// Scenario: An intersection encapsulates t and object
// p63
TEST (TestRays, IntersectionEncapsulatesTAndObject) {
    Sphere s = Sphere();
    Intersection i = Intersection(3.5, s);

    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.object, s);
}

// Scenario: Aggregating intersections
// p64
TEST (TestRays, AggregatingIntersections) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, s);
    Intersection i2 = Intersection(2, s);

    Intersections xs = Intersections(std::vector<Intersection> {i1, i2});
    EXPECT_EQ(xs.count, 2);
    EXPECT_EQ(xs[0].object, s);
    EXPECT_EQ(xs[1].object, s);
}
