#include "ray_tracer.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>


// Scenario: Creating a world
// p92
TEST (TestWorld, CreatingAWorld) {
    World w = World();

    EXPECT_EQ(w.objects.size(), 0);
    EXPECT_EQ(w.lights.size(), 0);
}

// Scenario: Creating a default world
// p92
TEST (TestWorld, DefaultWorld) {

    PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1 = Sphere();
    s1.set_material(
        Material(
            Color(0.8, 1.0, 0.6),  // color
            0.1,  // ambient
            0.7,  // diffuse
            0.2,  // specular
            200.0  // shininess
        )
    );
    Sphere s2 = Sphere();
    s2.set_transform(scaling_matrix(0.5, 0.5, 0.5));

    World w = default_world();

    EXPECT_THAT(w.objects, testing::Contains(s1));
    EXPECT_THAT(w.objects, testing::Contains(s2));
}

// Scenario: Intersect a world with a ray
// p93
TEST (TestWorld, IntersectWorldWithRay) {

    World w = default_world();
    Ray r(point(0, 0, -5), vector(0, 0, 1));

    Intersections xs = w.intersect_world(r);

    EXPECT_EQ(xs.count, 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}

// Scenario: Precomputing the state of an intersection
// p93
TEST (TestWorld, PrecomputingIntersection) {

    Ray r(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(4.0, s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, point(0, 0, -1));
    EXPECT_EQ(comps.eyev, vector(0, 0, -1));
    EXPECT_EQ(comps.normalv, vector(0, 0, -1));
}

// Scenario: Precomputing the hit from outside
// p93
TEST (TestWorld, PrecomputingHitInterior) {

    Ray r(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(4.0, s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(comps.inside, false);
}

// Scenario: Precomputing the hit from inside
// p95
TEST (TestWorld, PrecomputingHitExterior) {

    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(1, s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, point(0, 0, 1));
    EXPECT_EQ(comps.eyev, vector(0, 0, -1));
    EXPECT_EQ(comps.inside, true);
    // Normal inverted
    EXPECT_EQ(comps.normalv, vector(0, 0, -1));
}

// Scenario: Shading an intersection
// p95
TEST (TestWorld, ShadingIntersection) {

    World w = default_world();
    Ray r(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = w.objects[0];
    Intersection i = Intersection(4, s);

    Computation comps = prepare_computations(i, r);
    Color c = w.shade_hit(comps);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

// Scenario: Shading an intersection from the inside
// p95
TEST (TestWorld, ShadingIntersectionFromInside) {

    World w = default_world();
    w.lights[0] = PointLight(point(0, 0.25, 0), Color(1, 1, 1));
    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = w.objects[1];
    Intersection i = Intersection(0.5, s);

    Computation comps = prepare_computations(i, r);
    Color c = w.shade_hit(comps);

    EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

// Scenario: The colour when a ray misses
// p96
TEST (TestWorld, MissColor) {

    World w = default_world();
    Ray r(point(0, 0, -5), vector(0, 1, 0));

    Color c = w.color_at(r);

    EXPECT_EQ(c, Color(0, 0, 0));
}

// Scenario: The colour when a ray hit
// p96
TEST (TestWorld, HitColor) {

    World w = default_world();
    Ray r(point(0, 0, -5), vector(0, 0, 1));

    Color c = w.color_at(r);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

// Scenario: The colour when a ray hit
// p97
TEST (TestWorld, HitColorBehindRay) {

    World w = default_world();

    Material m1 = w.objects[0].get_material();
    m1.ambient = 1;
    w.objects[0].set_material(m1);

    Material m2 = w.objects[1].get_material();
    m2.ambient = 1;
    w.objects[1].set_material(m2);

    Ray r(point(0, 0, 0.75), vector(0, 0, -1));

    Color c = w.color_at(r);

    EXPECT_EQ(c, m2.color);
}
