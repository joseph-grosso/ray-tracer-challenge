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

// Scenario: getting a single row 2
// pMe
TEST (TestMatrices, GettingSingleRow_1) {
    std::vector<float> input = {1, 2, 3, 4,
                                5, 6, 7, 8,
                                9, 8, 7, 6,
                                5, 4, 3, 2};
    Matrix m(4, 4, input);
    std::vector<float> expected = {9, 8, 7, 6};
    EXPECT_TRUE(m.get_row(2) == expected);
}


// Scenario: getting a single row 2
// pMe
TEST (TestMatrices, GettingSingleRow_2) {
    std::vector<float> input = {1, 2, 3, 4,
                                5, 6, 7, 8,
                                9, 8, 7, 6,
                                5, 4, 3, 2};
    Matrix m(2, 8, input);
    std::vector<float> expected = {1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_TRUE(m.get_row(0) == expected);
}

// TODO: Remove once you're done debugging tests.
template <typename S>
std::ostream& operator<<(std::ostream& os,
                    const std::vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}

// Scenario: getting a single column
// pMe
TEST (TestMatrices, GettingSingleColumn_1) {
    std::vector<float> input = {1,   2,  3,  4,
                                5,   6,  7,  8,
                                9,  10, 11, 12,
                                13, 14, 15, 16};
    Matrix m(4, 4, input);
    std::vector<float> expected = {3, 7, 11, 15};
    EXPECT_TRUE(m.get_column(2) == expected);
}

// Scenario: getting a single column, part 2
// pMe
TEST (TestMatrices, GettingSingleColumn_2) {
    std::vector<float> input = {1,   2,  3,  4,
                                5,   6,  7,  8,
                                9,  10, 11, 12,
                                13, 14, 15, 16};
    Matrix m(2, 8, input);
    std::vector<float> expected = {3, 11};
    std::cout << m.get_column(2) << std::endl;
    EXPECT_TRUE(m.get_column(2) == expected);
}


// Scenario: Matrix multiplication, part 1
// p28
TEST (TestMatrices, MatrixMultiplication_1) {
    std::vector<float> in_1 = {1, 2, 3, 4,
                             5, 6, 7, 8,
                             9, 8, 7, 6,
                             5, 4, 3, 2};
    std::vector<float> in_2 = {-2, 1, 2, 3,
                             3, 2, 1, -1,
                             4, 3, 6, 5,
                             1, 2, 7, 8};
    std::vector<float> out = {20, 22, 50, 48,
                              44, 54, 114, 108,
                              40, 58, 110, 102,
                              16, 26, 46, 42};

    Matrix m1(4, 4, in_1);
    Matrix m2(4, 4, in_2);
    Matrix expected(4, 4, out);
    Matrix actual = m1 * m2;

    EXPECT_TRUE(expected == actual);
}

// Scenario: Matrix multiplication, part 1
// p28
TEST (TestMatrices, MatrixMultiplication_2) {
    std::vector<float> in_1 = {1, 2, 3, 4,
                             5, 6, 7, 8};
    std::vector<float> in_2 = {-2, 1,
                                3, 2,
                                4, 3,
                                1, 2};
    std::vector<float> out = {20, 22, 
                              44, 54};
    Matrix m1(2, 4, in_1);
    Matrix m2(4, 2, in_2);
    Matrix expected(2, 2, out);
    Matrix actual = m1 * m2;
    EXPECT_TRUE(expected == actual);
}
