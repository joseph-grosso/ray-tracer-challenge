#include <string>
#include <vector>
#include <iostream>
#include "tuple.h"
#include "matrix.h"
#include "gtest/gtest.h"


// Scenario: Constructing and inspecting a 4x4 matrix
// p26
TEST (TestMatrices, Inspecting4x4Matrix) {
    std::vector<float> m = {1   , 2   , 3   , 4,
                            5.5 , 6.5 , 7.5 , 8.5,
                            9   , 10  , 11  , 12,
                            13.5, 14.5, 15.5, 16.5};
    Matrix mat(4, 4, m);
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 0), 1));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 3), 4));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 0), 5.5));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 2), 7.5));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(2, 2), 11));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(3, 0), 13.5));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(3, 2), 15.5));
}

// Scenario: Constructing a 2x2 matrix
// p26
TEST (TestMatrices, Inspecting2x2Matrix) {
    std::vector<float> m = {-3,  5,
                            1 , -2};
    Matrix mat(2, 2, m);
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 0), -3));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 1), 5));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 0), 1));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 1), -2));
}

// Scenario: Constructing a 3x3 matrix
// p26
TEST (TestMatrices, Inspecting3x3Matrix) {
    std::vector<float> m = {-3,  5,  0,
                            1 , -2, -7,
                            0,   1,  1};
    Matrix mat(3, 3, m);
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 0), -3));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 1), -2));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(2, 2), 1));
}



