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

// #include <algorithm>
// #include <numeric>
#include <cmath>


// Scenario: Normal of a sphere at the X axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtX) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(1, 0, 0);

    EXPECT_EQ(n, vector(1, 0, 0));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at the Y axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtY) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(0, 1, 0);

    EXPECT_EQ(n, vector(0, 1, 0));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at the Z axis
// p78
TEST (TestLightingAndShading, NormalOfSphereAtZ) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(0, 0, 1);

    EXPECT_EQ(n, vector(0, 0, 1));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfSphereAtNonAxis) {
    Sphere s = Sphere();
    Tuple n = s.normal_at(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3);

    EXPECT_EQ(n, vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));
    EXPECT_EQ(n, n.normalize());
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfTranslatedSphere) {
    Sphere s = Sphere();
    s.set_transform(translation_matrix(0, 1, 0));
    Tuple n = s.normal_at(0, 1.70711, -0.70711);

    EXPECT_EQ(n, vector(0, 0.70711, -0.70711));
}

// Scenario: Normal of a sphere at a non axial point
// p78
TEST (TestLightingAndShading, NormalOfTransformedSphere) {
    Sphere s = Sphere();
    s.set_transform(scaling_matrix(1, 0.5, 1) * rotation_z_matrix(M_PI/5));

    Tuple n = s.normal_at(0, std::sqrt(2)/2, -std::sqrt(2)/2);

    EXPECT_EQ(n, vector(0, 0.97014, -0.24254));
}

// Scenario: Reflect a vector in a normal approaching at 45 deg.
// p83
TEST (TestLightingAndShading, ReflectInNormal) {
    Tuple v = vector(1, -1, 0);
    Tuple n = vector(0, 1, 0);
    EXPECT_EQ(v.reflect(n), vector(1, 1, 0));
}

// Scenario: Reflect a vector off a slanted surface.
// p83
TEST (TestLightingAndShading, ReflectInSlantedSurface) {
    Tuple v = vector(0, -1, 0);
    Tuple n = vector(std::sqrt(2)/2, std::sqrt(2)/2, 0);
    EXPECT_EQ(v.reflect(n), vector(1, 0, 0));
}
