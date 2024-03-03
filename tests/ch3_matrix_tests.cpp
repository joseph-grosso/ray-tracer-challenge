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
// p27
TEST (TestMatrices, Inspecting2x2Matrix) {
    std::vector<float> m = {-3,  5,
                            1 , -2};
    Matrix mat(2, 2, m);
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 0), -3));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 1), 5));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 0), 1));
    EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 1), -2));
}

// Scenario: Comparing 2 equal matrices
// p27
TEST (TestMatrices, Comparing2EqualMatrices) {
    std::vector<float> input = {1, 2, 3, 4,
                                5, 6, 7, 8,
                                9, 8, 7, 6,
                                5, 4, 3, 2};
    Matrix a(4, 4, input);
    Matrix b(4, 4, input);
    EXPECT_TRUE(a == b);
}

// Scenario: Comparing 2 unequal matrices
// p27
TEST (TestMatrices, Comparing2UnequalMatrices) {
    std::vector<float> input_1 = {1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  9, 8, 7, 6,
                                  5, 4, 3, 2};
    std::vector<float> input_2 = {2, 3, 4, 5,
                                  6, 7, 8, 9,
                                  8, 7, 6, 5,
                                  4, 3, 2, 1};
    Matrix a(4, 4, input_1);
    Matrix b(4, 4, input_2);
    EXPECT_TRUE(a != b);
}



