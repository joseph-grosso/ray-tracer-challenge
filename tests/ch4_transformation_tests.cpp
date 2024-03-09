#include <string>
#include <vector>
#include <iostream>
#include "tuple.h"
#include "matrix.h"
#include "transform.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>
#include <cmath>


// Scenario: Translating a Point
// p45
TEST (TestTranslations, TranslatePoint) {
    Matrix A = translation_matrix(5, -3, 2);
    Tuple p = point(-3, 4, 5);

    EXPECT_EQ(A * p, point(2, 1, 7));
}

// Scenario: Translating a Point By Inverse
// p45
TEST (TestTranslations, TranslatePointByInverse) {
    Matrix A = translation_matrix(5, -3, 2);
    Tuple p = point(-3, 4, 5);

    EXPECT_EQ(A.inverse() * p, point(-8, 7, 3));
}

// Scenario: Translating a Vector gives back the same vector
// p45
TEST (TestTranslations, TranslateVector) {
    Matrix A = translation_matrix(5, -3, 2);
    Tuple v = vector(-3, 4, 5);

    EXPECT_EQ(A * v, v);
}

// Scenario: Scaling a Point
// p46
TEST (TestTranslations, ScalePoint) {
    Matrix A = scaling_matrix(2, 3, 4);
    Tuple p = point(-4, 6, 8);

    EXPECT_EQ(A * p, point(-8, 18, 32));
}

// Scenario: Scaling a Vector
// p46
TEST (TestTranslations, ScaleVector) {
    Matrix A = scaling_matrix(2, 3, 4);
    Tuple v = vector(-4, 6, 8);

    EXPECT_EQ(A * v, vector(-8, 18, 32));
}

// Scenario: Scaling a Vector by Inverse
// p46
TEST (TestTranslations, ScaleVectorByInverse) {
    Matrix A = scaling_matrix(2, 3, 4);
    Tuple v = vector(-4, 6, 8);

    EXPECT_EQ(A.inverse() * v, vector(-2, 2, 2));
}

// Scenario: Reflection of point
// p47
TEST (TestTranslations, ReflectPointWithScaling) {
    Matrix A = scaling_matrix(-1, 1, 1);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(A * p, point(-2, 3, 4));
}

// Scenario: Rotation in the x axis
// p48
TEST (TestTranslations, XAxisRotation) {
    const float pi = 3.14159265359;
    Matrix half_quarter = rotation_x_matrix(pi / 4);
    Matrix full_quarter = rotation_x_matrix(pi / 2);
    Tuple p = point(0, 1, 0);

    EXPECT_EQ(half_quarter * p, point(0, std::sqrt(2)/2, std::sqrt(2)/2));
    EXPECT_EQ(full_quarter * p, point(0, 0, 1));
}

// Scenario: Rotation in the x axis - inverse
// p49
TEST (TestTranslations, XAxisRotationInverse) {
    const float pi = 3.14159265359;
    Matrix half_quarter = rotation_x_matrix(pi / 4);
    Tuple p = point(0, 1, 0);

    EXPECT_EQ(half_quarter.inverse() * p, point(0, std::sqrt(2)/2, -std::sqrt(2)/2));
}

// Scenario: Rotation in the y axis
// p49
TEST (TestTranslations, YAxisRotation) {
    const float pi = 3.14159265359;
    Matrix half_quarter = rotation_y_matrix(pi / 4);
    Matrix full_quarter = rotation_y_matrix(pi / 2);
    Tuple p = point(0, 0, 1);

    EXPECT_EQ(half_quarter * p, point(std::sqrt(2)/2, 0, std::sqrt(2)/2));
    EXPECT_EQ(full_quarter * p, point(1, 0, 0));
}

// Scenario: Shearing X in proportion to Y
// p52
TEST (TestTranslations, ShearingXInPropToY) {
    Matrix shear = shearing_matrix(1, 0, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(5, 3, 4));
}

// Scenario: Shearing X in proportion to Z
// p52
TEST (TestTranslations, ShearingXInPropToZ) {
    Matrix shear = shearing_matrix(0, 1, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(6, 3, 4));
}

// Scenario: Shearing Y in proportion to X
// p52
TEST (TestTranslations, ShearingYInPropToX) {
    Matrix shear = shearing_matrix(0, 0, 1, 0, 0, 0);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(2, 5, 4));
}

// Scenario: Shearing Y in proportion to Z
// p52
TEST (TestTranslations, ShearingYInPropToZ) {
    Matrix shear = shearing_matrix(0, 0, 0, 1, 0, 0);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(2, 7, 4));
}

// Scenario: Shearing Z in proportion to X
// p52
TEST (TestTranslations, ShearingZInPropToX) {
    Matrix shear = shearing_matrix(0, 0, 0, 0, 1, 0);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(2, 3, 6));
}

// Scenario: Shearing Z in proportion to Y
// p53
TEST (TestTranslations, ShearingZInPropToY) {
    Matrix shear = shearing_matrix(0, 0, 0, 0, 0, 1);
    Tuple p = point(2, 3, 4);

    EXPECT_EQ(shear * p, point(2, 3, 7));
}
