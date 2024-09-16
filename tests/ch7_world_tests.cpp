#include "ray_tracer.h"
#include "gtest/gtest.h"
#include <math.h>
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
    Intersection i = Intersection(4.0, &s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(*comps.object, *i.object);
    EXPECT_EQ(comps.point, point(0, 0, -1));
    EXPECT_EQ(comps.eyev, vector(0, 0, -1));
    EXPECT_EQ(comps.normalv, vector(0, 0, -1));
}

// Scenario: Precomputing the hit from outside
// p93
TEST (TestWorld, PrecomputingHitInterior) {

    Ray r(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(4.0, &s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(comps.inside, false);
}

// Scenario: Precomputing the hit from inside
// p95
TEST (TestWorld, PrecomputingHitExterior) {

    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(1, &s);

    Computation comps = prepare_computations(i, r);

    EXPECT_EQ(*comps.object, *i.object);
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
    Intersection i = Intersection(4, &s);

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
    Intersection i = Intersection(0.5, &s);

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

// Chapter 7: Making a Scene
// Defining a view transform
// Scenario: The transform matrix for the default orientation
// p98
TEST (TestCameraTransform, DefaultOrientation) {

    Tuple from = point(0, 0, 0);
    Tuple to = point(0, 0, -1);
    Tuple up = vector(0, 1, 0);
    
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, identity_matrix(4));
}

// Scenario: The transform matrix looking in the z direction
// p98
TEST (TestCameraTransform, ZDirectionCameraOrientation) {

    Tuple from = point(0, 0, 0);
    Tuple to = point(0, 0, 1);
    Tuple up = vector(0, 1, 0);
    
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, scaling_matrix(-1, 1, -1));
}

// Scenario: The transform matrix moves the world
// p99
TEST (TestCameraTransform, TranslationOrientation) {

    Tuple from = point(0, 0, 8);
    Tuple to = point(0, 0, 0);
    Tuple up = vector(0, 1, 0);
    
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, translation_matrix(0, 0, -8));
}

// Scenario: The transform matrix moves the world
// p99
TEST (TestCameraTransform, ArbitraryTransform) {

    Tuple from = point(1, 3, 2);
    Tuple to = point(4, -2, 8);
    Tuple up = vector(1, 1, 0);
    
    Matrix actual = view_transform(from, to, up);
    Matrix expected(
        4,
        4,
        std::vector<float>{
            -0.50709, 0.50709,  0.67612, -2.36643,
             0.76772, 0.60609,  0.12122, -2.82843,
            -0.35857, 0.59761, -0.71714,  0.00000,
             0.00000, 0.00000,  0.00000,  1.00000
        }
    );
    EXPECT_EQ(expected, actual);
}

// Scenario: Constructing a camera
// p101
TEST (TestCamera, ConstructingCamera) {

    int hsize = 160;
    int vsize = 120;
    float field_of_view = M_PI / 2;

    Camera c(hsize, vsize, field_of_view);

    EXPECT_EQ(c.hsize, 160);
    EXPECT_EQ(c.vsize, 120);
    EXPECT_TRUE(equalByEpsilon(c.field_of_view, M_PI / 2));
    EXPECT_EQ(c.transform, Matrix(4));
}

// Scenario: The pixel size for a horizontal canvas
// p101
TEST (TestCamera, CamPixelSizeHorizontal) {
    Camera c(200, 125, M_PI / 2);

    EXPECT_TRUE(equalByEpsilon(c.pixel_size, 0.01));
}

// Scenario: The pixel size for a vertical canvas
// p101
TEST (TestCamera, CamPixelSizeVertical) {
    Camera c(125, 200, M_PI / 2);

    EXPECT_TRUE(equalByEpsilon(c.pixel_size, 0.01));
}

// Scenario: Constructing a ray through the center of the canvas
// p103
TEST (TestCamera, RayThruCenterOfCanvas) {
    Camera c(201, 101, M_PI / 2);

    Ray r = c.ray_for_pixel(100, 50);

    EXPECT_EQ(r.get_origin(), point(0, 0, 0));
    EXPECT_EQ(r.get_direction(), vector(0, 0, -1));
}

// Scenario: Constructing a ray through a corner of the canvas
// p103
TEST (TestCamera, RayThruCornerOfCanvas) {
    Camera c(201, 101, M_PI / 2);

    Ray r = c.ray_for_pixel(0, 0);

    EXPECT_EQ(r.get_origin(), point(0, 0, 0));
    EXPECT_EQ(r.get_direction(), vector(0.66519, 0.33259, -0.66851));
}

// Scenario: Constructing a ray when the camera is transformed
// p103
TEST (TestCamera, RayThruCameraTransformed) {
    Camera c(201, 101, M_PI / 2);
    c.transform = rotation_y_matrix(M_PI / 4) * translation_matrix(0, -2, 5);

    Ray r = c.ray_for_pixel(100, 50);

    EXPECT_EQ(r.get_origin(), point(0, 2, -5));
    EXPECT_EQ(r.get_direction(), vector(std::sqrt(2) / 2, 0, -std::sqrt(2) / 2));
}

// Scenario: Render a world with a camera
// p104
TEST (TestCamera, RenderWorld) {
    World w = default_world();
    Camera c(11, 11, M_PI / 2);

    Tuple from = point(0, 0, -5);
    Tuple to = point(0, 0, 0);
    Tuple up = vector(0, 1, 0);

    c.transform = view_transform(from, to, up);

    Canvas image = c.render(w);

    EXPECT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}

// Scenario: Render a world with a camera with different pixel widths
// pMe
TEST (TestCamera, RenderWorldDifferentWidths) {
    World w = default_world();
    Camera c(11, 21, M_PI / 2);

    Tuple from = point(0, 0, -5);
    Tuple to = point(0, 0, 0);
    Tuple up = vector(0, 1, 0);

    c.transform = view_transform(from, to, up);
    
    Canvas image = c.render(w);

    EXPECT_EQ(image.pixel_at(5, 10), Color(0.38066, 0.47583, 0.2855));
}

// Scenario: Render a world with a camera with different pixel widths
// pMe
TEST (TestCamera, RenderWorldDifferentWidths2) {
    World w = default_world();
    Camera c(21, 11, M_PI / 2);

    Tuple from = point(0, 0, -5);
    Tuple to = point(0, 0, 0);
    Tuple up = vector(0, 1, 0);

    c.transform = view_transform(from, to, up);
    
    Canvas image = c.render(w);

    EXPECT_EQ(image.pixel_at(10, 5), Color(0.38066, 0.47583, 0.2855));
}
