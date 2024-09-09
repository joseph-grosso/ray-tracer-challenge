#include "ray_tracer.h"
#include "gtest/gtest.h"
#include <math.h>
#include <gmock/gmock.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

class TestShape : public Shape {
    public:
        // default ray
        Ray saved_ray = Ray(
            point(0, 0, 0),
            vector(1, 0, 0)
        );
        Intersections local_intersect(Ray r) {
            this->saved_ray = r;
            return Intersections();
        };
};


// Chapter 9: Refactoring Shapes
// Scenario: The default transformation
// p119
TEST (TestAbstractShape, DefaultTransform) {
    TestShape s = TestShape();

    EXPECT_EQ(s.get_transform(), identity_matrix(4));
}

// Scenario: Assigning a transformation
// p119
TEST (TestAbstractShape, AssignedTransform) {
    TestShape s = TestShape();
    s.set_transform(translation_matrix(2, 3, 4));
    EXPECT_EQ(s.get_transform(), translation_matrix(2, 3, 4));
}


// Scenario: The default material
// p119
TEST (TestAbstractShape, DefaultMaterial) {
    Material m = Material();
    TestShape s = TestShape();
    EXPECT_EQ(m, s.get_material());
}

// Scenario: Assigning a material
// p119
TEST (TestAbstractShape, AssigningMaterial) {
    Material m = Material();
    TestShape s = TestShape();

    m.ambient = 1;
    s.set_material(m);

    EXPECT_EQ(m, s.get_material());
}

// Scenario: Intersecting a scaled shape with a ray
// p120
TEST (TestAbstractShape, IntersectScaledShape) {
    TestShape s = TestShape();
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

    s.set_transform(scaling_matrix(2, 2, 2));
    Intersections xs = s.intersect(r);

    EXPECT_EQ(s.saved_ray.get_origin(), point(0, 0, -2.5));
    EXPECT_EQ(s.saved_ray.get_direction(), vector(0, 0, 0.5));
}

// Scenario: Intersecting a translated shape with a ray
// p120
TEST (TestAbstractShape, IntersectTranslatedShape) {
    TestShape s = TestShape();
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

    s.set_transform(translation_matrix(5, 0, 0));
    Intersections xs = s.intersect(r);

    EXPECT_EQ(xs.count, 0);
}

// // Scenario: Computing the normal of a sphere on a translated shape
// // p121
// // TODO: Delete original tests as they are no longer needed (refactor on p121)
// TEST (TestAbstractShape, NormalOfTranslatedSphere) {
//     TestShape s = TestShape();
//     s.set_transform(translation_matrix(0, 1, 0));
//     Tuple n = s.normal_at(0, 1.70711, -0.70711);

//     EXPECT_EQ(n, vector(0, 0.70711, -0.70711));
// }

// // Scenario: Computing the normal on a transformed shape
// // p121
// // TODO: Delete original tests as they are no longer needed (refactor on p121)
// TEST (TestAbstractShape, NormalOfTransformedSphere) {
//     TestShape s = TestShape();
//     s.set_transform(scaling_matrix(1, 0.5, 1) * rotation_z_matrix(M_PI/5));

//     Tuple n = s.normal_at(0, std::sqrt(2)/2, -std::sqrt(2)/2);

//     EXPECT_EQ(n, vector(0, 0.97014, -0.24254));
// }
