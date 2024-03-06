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
    EXPECT_EQ(a, b);
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
    EXPECT_NE(a, b);
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
    EXPECT_EQ(m.get_row(2), expected);
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
    EXPECT_EQ(m.get_row(0), expected);
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
    EXPECT_EQ(m.get_column(2), expected);
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
    EXPECT_EQ(m.get_column(2), expected);
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

    EXPECT_EQ(expected, actual);
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
    EXPECT_EQ(expected, actual);
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
    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
}

// Scenario: Calculate 2x2 matrix determinant
// p34
TEST (TestMatrices, DeterminantOf2x2) {
    std::vector<float> data = {1, 5,
                            -3, 2};

    Matrix m(2, 2, data);
    float expected = 17;
    float actual = m.determinant();

    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
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

    EXPECT_EQ(expected, actual);
}

// Scenario: Calculating a minor of a 3x3 matrix
// p35
TEST (TestMatrices, MinorOf3x3) {
    std::vector<float> a_data = {3, 5, 0,
                            2, -1, -7,
                            6, -1, 5};

    Matrix a(3, 3, a_data);
    Matrix b = a.submatrix(1, 0);

    EXPECT_EQ(25, b.determinant());
    EXPECT_EQ(25, a.minor(1, 0));
}

// Scenario: Calculating a cofactor of a 3x3 matrix
// p36
TEST (TestMatrices, CofactorOf3x3) {
    std::vector<float> a_data = {3, 5, 0,
                            2, -1, -7,
                            6, -1, 5};

    Matrix a(3, 3, a_data);

    EXPECT_EQ(a.minor(1, 0), 25);
    EXPECT_EQ(a.cofactor(1, 0), -25);
    EXPECT_EQ(a.minor(0, 0), -12);
    EXPECT_EQ(a.cofactor(0, 0), -12);
}

// Scenario: Calculating the determinant of a 3x3 matrix
// p37
TEST (TestMatrices, DeterminantOf3x3) {
    std::vector<float> a_data = {1, 2, 6,
                                -5, 8, -4,
                                2, 6, 4};

    Matrix a(3, 3, a_data);

    EXPECT_EQ(a.cofactor(0, 0), 56);
    EXPECT_EQ(a.cofactor(0, 1), 12);
    EXPECT_EQ(a.cofactor(0, 2), -46);
    EXPECT_EQ(a.determinant(), -196);
}

// Scenario: Calculating the determinant of a 4x4 matrix
// p37
TEST (TestMatrices, DeterminantOf4x4) {
    std::vector<float> a_data = {-2, -8, 3, 5,
                                 -3, 1, 7, 3,
                                 1, 2, -9, 6,
                                 -6, 7, 7, -9};

    Matrix a(4, 4, a_data);

    EXPECT_EQ(a.cofactor(0, 0), 690);
    EXPECT_EQ(a.cofactor(0, 1), 447);
    EXPECT_EQ(a.cofactor(0, 2), 210);
    EXPECT_EQ(a.cofactor(0, 3), 51);
    EXPECT_EQ(a.determinant(), -4071);
}

// Scenario: Testing an invertible matrix for invertibility
// p39
TEST (TestMatrices, InvertibleMatrix) {
    std::vector<float> a_data = {6, 4, 4, 4,
                                 5, 5, 7, 6,
                                 4, -9, 3, -7,
                                 9, 1, 7, -6};

    Matrix a(4, 4, a_data);

    EXPECT_EQ(a.determinant(), -2120);
    EXPECT_TRUE(a.is_invertible());
}

// Scenario: Testing a non-invertible matrix for invertibility
// p39
TEST (TestMatrices, NonInvertibleMatrix) {
    std::vector<float> a_data = {-4, 2, -2, -3,
                                 9, 6, 2, 6,
                                 0, -5, 1, -5,
                                 0, 0, 0, 0};

    Matrix a(4, 4, a_data);

    EXPECT_EQ(a.determinant(), 0);
    EXPECT_TRUE(!a.is_invertible());
}

// Scenario: Calculating the inverse of a matrix
// p39
TEST (TestMatrices, CalculateInverse) {
    std::vector<float> a_data = {-5, 2, 6, -8,
                                 1, -5, 1, 8,
                                 7, 7, -6, -7,
                                 1, -3, 7, 4};
    std::vector<float> b_expected_data = 
        { 0.21805,  0.45113,  0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361,  0.52068,
        -0.07895, -0.22368, -0.05263,  0.19737,
        -0.52256, -0.81391, -0.30075,  0.30639};
    
    Matrix a(4, 4, a_data);
    Matrix b = a.inverse();
    Matrix expected(4, 4, b_expected_data);

    EXPECT_EQ(a.determinant(), 532);
    EXPECT_EQ(a.cofactor(2, 3), -160);
    EXPECT_TRUE(equalByEpsilon(b.get_point(3, 2), -160 / (float) 532));
    EXPECT_EQ(a.cofactor(3, 2), 105);
    EXPECT_EQ(b.get_point(2, 3), 105 / (float) 532);
    EXPECT_EQ(expected, b);
}

// Scenario: Calculating the inverse of a matrix p2
// p41
TEST (TestMatrices, CalculateInverse_2) {
    std::vector<float> a_data = { 8, -5,  9,  2,
                                 7,  5,  6,  1,
                                -6,  0,  9,  6,
                                -3,  0, -9, -4};
    std::vector<float> expected_data = {-0.15385, -0.15385, -0.28205, -0.53846,
                                        -0.07692,  0.12308,  0.02564,  0.03077,
                                         0.35897,  0.35897,  0.43590,  0.92308,
                                        -0.69231, -0.69231, -0.76923, -1.92308};
    
    Matrix a(4, 4, a_data);
    Matrix expected(4, 4, expected_data);

    EXPECT_EQ(expected, a.inverse());
}

// Scenario: Calculating the inverse of a matrix p3
// p41
TEST (TestMatrices, CalculateInverse_3) {
    std::vector<float> a_data = { 9, 3,  0,  9,
                                 -5,  -2,  -6,  -3,
                                -4,  9,  6,  4,
                                -7,  6, 6, 2};
    std::vector<float> expected_data = {-0.04074, -0.07778,  0.14444, -0.22222,
                                        -0.07778,  0.03333,  0.36667, -0.33333,
                                        -0.02901, -0.14630, -0.10926,  0.12963,
                                         0.17778,  0.06667, -0.26667,  0.33333};
    
    Matrix a(4, 4, a_data);
    Matrix expected(4, 4, expected_data);

    // std::cout << a.inverse().get_matrix_data() << std::endl;
    // std::cout << expected.get_matrix_data() << std::endl;

    EXPECT_EQ(expected, a.inverse());
}

// Scenario: Multiply a product by its inverse
// p41
TEST (TestMatrices, MultiplyByInverse) {
    std::vector<float> a_data = {3, -9, 7, 3,
                                3, -8, 2, -9,
                                -4, 4, 4, 1,
                                -6, 5, -1, 1};
    std::vector<float> b_data = {8, 2, 2, 2,
                                3, -1, 7, 0,
                                7, 0, 5, 4,
                                6, -2, 0, 5};

    Matrix a(4, 4, a_data);
    Matrix b(4, 4, b_data);
    Matrix b_1 = b.inverse();
    Matrix c = a * b;

    std::cout << a.get_matrix_data() << std::endl;
    std::cout << (c * b_1).get_matrix_data() << std::endl;
    std::cout << (b * b_1).get_matrix_data() << std:: endl;

    EXPECT_EQ(c * b_1, a);
}

