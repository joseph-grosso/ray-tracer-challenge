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

// Scenario: Matrix multiplication, part 2
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

// Scenario: Matrix multiplication with a tuple
// p30
TEST (TestMatrices, MatrixMultWithTuple) {
    std::vector<float> input_m = {1, 2, 3, 4,
                             2, 4, 4, 2,
                             8, 6, 4, 1,
                             0, 0, 0, 1};
    Matrix m(4, 4, input_m);
    Tuple t(1, 2, 3, 1);
    Tuple expected(18, 24, 33, 1);
    Tuple actual = m * t;
    EXPECT_TRUE(expected == actual);
}

// Scenario: Matrix multiplication with an identity matrix
// p32
TEST (TestMatrices, MatrixMultWithIdentity) {
    std::vector<float> in_1 = {1, 2, 3, 4,
                             5, 6, 7, 8,
                             9, 8, 7, 6,
                             5, 4, 3, 2};
    std::vector<float> in_2 = {1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1};

    Matrix m(4, 4, in_1);
    Matrix I(4, 4, in_2);
    Matrix expected(4, 4, in_1);
    Matrix actual = m * I;

    EXPECT_TRUE(expected == actual);
}

// Scenario: Matrix transpose
// p33
TEST (TestMatrices, MatrixTranspose) {
    std::vector<float> input = {0, 9, 3, 0,
                                9, 8, 0, 8,
                                1, 8, 5, 3,
                                0, 0, 5, 8};
    std::vector<float> in_exp = {0, 9, 1, 0,
                               9, 8, 8, 0,
                               3, 0, 5, 5,
                               0, 8, 3, 8};

    Matrix m(4, 4, input);
    Matrix expected(4, 4, in_exp);
    Matrix actual = m.transpose();

    EXPECT_TRUE(expected == actual);
}

// Scenario: Matrix transpose non square matrix
// pMe
TEST (TestMatrices, MatrixTransposeNonSquareMatrix) {
    std::vector<float> input = {0, 9, 3, 0,
                                9, 8, 0, 8,
                                1, 8, 5, 3};
    std::vector<float> in_exp = {0, 9, 1,
                               9, 8, 8,
                               3, 0, 5,
                               0, 8, 3,};

    Matrix m(3, 4, input);
    Matrix expected(4, 3, in_exp);
    Matrix actual = m.transpose();

    EXPECT_TRUE(expected == actual);
}

// Scenario: Transpose Identity Matrix
// p33
TEST (TestMatrices, TransposeIdentityMatrix) {
    std::vector<float> Id = {1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1};

    Matrix I(4, 4, Id);
    Matrix expected(4, 4, Id);
    Matrix actual = I.transpose();

    EXPECT_TRUE(expected == actual);
}

// Scenario: Calculate 2x2 matrix determinant
// p34
TEST (TestMatrices, DeterminantOf2x2) {
    std::vector<float> data = {1, 5,
                            -3, 2};

    Matrix m(2, 2, data);
    float expected = 17;
    float actual = m.determinant();

    EXPECT_TRUE(expected == actual);
}

// Scenario: A submatrix of a 3x3 matrix is a 2x2 matrix
// p35
TEST (TestMatrices, SubmatrixOf3x3) {
    std::vector<float> in_data = {1, 5, 0,
                            -3, 2, 7,
                            0, 6, -3};
    std::vector<float> expected_data = {-3, 2,
                                        0, 6,};
    

    Matrix m(3, 3, in_data);
    Matrix expected(2, 2, expected_data);
    Matrix actual = m.submatrix(0, 2);

    EXPECT_TRUE(expected == actual);
}

// Scenario: A submatrix of a 4x4 matrix is a 3x3 matrix
// p35
TEST (TestMatrices, SubmatrixOf4x4) {
    std::vector<float> in_data = {-6, 1, 1, 6,
                            -8, 5, 8, 6,
                            -1, 0, 8, 2,
                            -7, 1, -1, 1};
    std::vector<float> expected_data = {-6, 1, 6,
                            -8, 8, 6,
                            -7, -1, 1};
    

    Matrix m(4, 4, in_data);
    Matrix expected(3, 3, expected_data);
    Matrix actual = m.submatrix(2, 1);

    EXPECT_TRUE(expected == actual);
}


// Scenario: Calculating a minor of a 3x3 matrix
// p35
TEST (TestMatrices, MinorOf3x3) {
    std::vector<float> a_data = {3, 5, 0,
                            2, -1, -7,
                            6, -1, 5};

    Matrix a(3, 3, a_data);
    Matrix b = a.submatrix(1, 0);

    EXPECT_TRUE(25 == b.determinant());
    EXPECT_TRUE(25 == a.minor(1, 0));
}