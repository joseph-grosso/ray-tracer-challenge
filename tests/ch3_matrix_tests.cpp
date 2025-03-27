#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "matrix.hpp"
#include "tuple.hpp"

// Scenario: Constructing and inspecting a 4x4 matrix
// p26
TEST(TestMatrices, Inspecting4x4Matrix) {
  std::vector<float> m = {
      1,    2,    3,    4,    // 4x4
      5.5,  6.5,  7.5,  8.5,  // 4x4
      9,    10,   11,   12,   // 4x4
      13.5, 14.5, 15.5, 16.5  // 4x4
  };
  Matrix mat(m);
  std::cout << mat.get_eigen_data() << std::endl;
  EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 0), 1));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(0, 3), 4));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 0), 5.5));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(1, 2), 7.5));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(2, 2), 11));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(3, 0), 13.5));
  EXPECT_TRUE(equalByEpsilon(mat.get_point(3, 2), 15.5));
}

// Scenario: Comparing 2 equal matrices
// p27
TEST(TestMatrices, Comparing2EqualMatrices) {
  std::vector<float> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  Matrix a(input);
  Matrix b(input);
  EXPECT_EQ(a, b);
}

// Scenario: Comparing 2 unequal matrices
// p27
TEST(TestMatrices, Comparing2UnequalMatrices) {
  std::vector<float> input_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  std::vector<float> input_2 = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  Matrix a(input_1);
  Matrix b(input_2);
  EXPECT_NE(a, b);
}

// Scenario: getting a single row
// pMe
TEST(TestMatrices, GettingSingleRow_1) {
  std::vector<float> input = {
      1, 2, 3, 4,  // 4x4
      5, 6, 7, 8,  // 4x4
      9, 8, 7, 6,  // 4x4
      5, 4, 3, 2   // 4x4
  };
  Matrix m(input);
  std::vector<float> expected = {9, 8, 7, 6};
  EXPECT_EQ(m.get_row(2), expected);
}

// Scenario: getting a single row 2
// pMe
TEST(TestMatrices, GettingSingleRow_2) {
  std::vector<float> input = {
      1, 2, 3, 4,  // 4x4
      5, 6, 7, 8,  // 4x4
      9, 8, 7, 6,  // 4x4
      5, 4, 3, 2   // 4x4
  };
  Matrix m(input);
  std::vector<float> expected = {1, 2, 3, 4};
  EXPECT_EQ(m.get_row(0), expected);
}

// Scenario: getting a single column
// pMe
TEST(TestMatrices, GettingSingleColumn_1) {
  std::vector<float> input = {1, 2,  3,  4,  5,  6,  7,  8,
                              9, 10, 11, 12, 13, 14, 15, 16};
  Matrix m(input);
  std::vector<float> expected = {3, 7, 11, 15};
  EXPECT_EQ(m.get_column(2), expected);
}

// Scenario: getting a single column, part 2
// pMe
TEST(TestMatrices, GettingSingleColumn_2) {
  std::vector<float> input = {
      1,  2,  3,  4,   // 4x4
      5,  6,  7,  8,   // 4x4
      9,  10, 11, 12,  // 4x4
      13, 14, 15, 16   // 4x4
  };
  Matrix m(input);
  std::vector<float> expected = {3, 7, 11, 15};
  EXPECT_EQ(m.get_column(2), expected);
}

// Scenario: Matrix multiplication, part 1
// p28
TEST(TestMatrices, MatrixMultiplication_1) {
  std::vector<float> in_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  std::vector<float> in_2 = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
  std::vector<float> out = {20, 22, 50,  48,  44, 54, 114, 108,
                            40, 58, 110, 102, 16, 26, 46,  42};

  Matrix m1(in_1);
  Matrix m2(in_2);
  Matrix expected(out);
  Matrix actual = m1 * m2;

  EXPECT_EQ(expected, actual);
}

// Scenario: Matrix multiplication with a tuple
// p30
TEST(TestMatrices, MatrixMultWithTuple) {
  std::vector<float> input_m = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
  Matrix m(input_m);
  Tuple t(1, 2, 3, 1);
  Tuple expected(18, 24, 33, 1);
  Tuple actual = m * t;
  EXPECT_EQ(expected, actual);
}

// Scenario: Matrix multiplication with an identity matrix
// p32
TEST(TestMatrices, MatrixMultWithIdentity) {
  std::vector<float> in_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  std::vector<float> in_2 = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  Matrix m(in_1);
  Matrix I(in_2);
  Matrix expected(in_1);
  Matrix actual = m * I;

  EXPECT_EQ(expected, actual);
}

// Scenario: Matrix transpose
// p33
TEST(TestMatrices, MatrixTranspose) {
  std::vector<float> input = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
  std::vector<float> in_exp = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};

  Matrix m(input);
  Matrix expected(in_exp);
  Matrix actual = m.transpose();

  EXPECT_EQ(expected, actual);
}

// Scenario: Matrix transpose non square matrix
// pMe
TEST(TestMatrices, MatrixTransposeNonSquareMatrix) {
  std::vector<float> input = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 0, 0};
  std::vector<float> in_exp = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 0, 0, 8, 3, 0};

  Matrix m(input);
  Matrix expected(in_exp);
  Matrix actual = m.transpose();

  EXPECT_EQ(expected, actual);
}

// Scenario: Transpose Identity Matrix
// p33
TEST(TestMatrices, TransposeIdentityMatrix) {
  std::vector<float> Id = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  Matrix I(Id);
  Matrix expected(Id);
  Matrix actual = I.transpose();

  EXPECT_EQ(expected, actual);
}

// Scenario: Calculating the determinant of a 4x4 matrix
// p37
TEST(TestMatrices, DeterminantOf4x4) {
  std::vector<float> a_data = {-2, -8, 3,  5, -3, 1, 7, 3,
                               1,  2,  -9, 6, -6, 7, 7, -9};

  Matrix a(a_data);

  EXPECT_TRUE(equalByEpsilon(a.determinant(), -4071));
}

// Scenario: Testing an invertible matrix for invertibility
// p39
TEST(TestMatrices, InvertibleMatrix) {
  std::vector<float> a_data = {6, 4,  4, 4,  5, 5, 7, 6,
                               4, -9, 3, -7, 9, 1, 7, -6};

  Matrix a(a_data);

  EXPECT_TRUE(equalByEpsilon(a.determinant(), -2120));
  EXPECT_TRUE(a.is_invertible());
}

// Scenario: Testing a non-invertible matrix for invertibility
// p39
TEST(TestMatrices, NonInvertibleMatrix) {
  std::vector<float> a_data = {-4, 2,  -2, -3, 9, 6, 2, 6,
                               0,  -5, 1,  -5, 0, 0, 0, 0};

  Matrix a(a_data);

  EXPECT_EQ(a.determinant(), 0);
  EXPECT_TRUE(!a.is_invertible());
}

// Scenario: Calculating the inverse of a matrix
// p39
TEST(TestMatrices, CalculateInverse) {
  std::vector<float> a_data = {-5, 2, 6,  -8, 1, -5, 1, 8,
                               7,  7, -6, -7, 1, -3, 7, 4};
  std::vector<float> b_expected_data = {0.21805,  0.45113,  0.24060,  -0.04511,
                                        -0.80827, -1.45677, -0.44361, 0.52068,
                                        -0.07895, -0.22368, -0.05263, 0.19737,
                                        -0.52256, -0.81391, -0.30075, 0.30639};

  Matrix a(a_data);
  Matrix b = a.inverse();
  Matrix expected(b_expected_data);

  EXPECT_TRUE(equalByEpsilon(a.determinant(), 532));
  EXPECT_TRUE(equalByEpsilon(b.get_point(3, 2), -160 / (float)532));
  EXPECT_TRUE(equalByEpsilon(b.get_point(2, 3), 105 / (float)532));
  EXPECT_EQ(expected, b);
}

// Scenario: Calculating the inverse of a matrix p2
// p41
TEST(TestMatrices, CalculateInverse_2) {
  std::vector<float> a_data = {8,  -5, 9, 2, 7,  5, 6,  1,
                               -6, 0,  9, 6, -3, 0, -9, -4};
  std::vector<float> expected_data = {-0.15385, -0.15385, -0.28205, -0.53846,
                                      -0.07692, 0.12308,  0.02564,  0.03077,
                                      0.35897,  0.35897,  0.43590,  0.92308,
                                      -0.69231, -0.69231, -0.76923, -1.92308};

  Matrix a(a_data);
  Matrix expected(expected_data);

  EXPECT_EQ(expected, a.inverse());
}

// Scenario: Calculating the inverse of a matrix p3
// p41
TEST(TestMatrices, CalculateInverse_3) {
  std::vector<float> a_data = {9,  3, 0, 9, -5, -2, -6, -3,
                               -4, 9, 6, 4, -7, 6,  6,  2};
  std::vector<float> expected_data = {-0.04074, -0.07778, 0.14444,  -0.22222,
                                      -0.07778, 0.03333,  0.36667,  -0.33333,
                                      -0.02901, -0.14630, -0.10926, 0.12963,
                                      0.17778,  0.06667,  -0.26667, 0.33333};
  Matrix a(a_data);
  Matrix expected(expected_data);

  EXPECT_EQ(expected, a.inverse());
}

// Scenario: Multiply a product by its inverse
// p41
TEST(TestMatrices, MultiplyByInverse) {
  std::vector<float> a_data = {3,  -9, 7, 3, 3,  -8, 2,  -9,
                               -4, 4,  4, 1, -6, 5,  -1, 1};
  std::vector<float> b_data = {8, 2, 2, 2, 3, -1, 7, 0,
                               7, 0, 5, 4, 6, -2, 0, 5};

  Matrix a(a_data);
  Matrix b(b_data);
  Matrix b_1 = b.inverse();
  Matrix c = a * b;

  EXPECT_EQ(c * b_1, a);
}

// Scenario: Inverting the identity matrix gives back the same matrix
// pMe
TEST(TestMatrices, InverseOfIdentity) {
  std::vector<float> id_1_data = {1, 0, 0, 0, 0, 1, 0, 0,
                                  0, 0, 1, 0, 0, 0, 0, 1};
  Matrix id_1(id_1_data);

  EXPECT_EQ(id_1, id_1.inverse());
}

// Scenario: The inverse of a matrix times the original matrix equals the
// identity matrix pMe
TEST(TestMatrices, InverseTimesOGIsIdentity_4x4) {
  std::vector<float> a_data = {9,  3, 0, 9, -5, -2, -6, -3,
                               -4, 9, 6, 4, -7, 6,  6,  2};
  std::vector<float> id_data = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  Matrix a(a_data);
  Matrix a_minus1 = a.inverse();

  Matrix out = a * a_minus1;
  Matrix id(id_data);

  EXPECT_EQ(id * a, a);
  EXPECT_EQ(a * a_minus1, id);
}

// Scenario: Inverting the identity matrix gives back the same matrix
// pMe
TEST(TestMatrices, InverseOfIdentity_2) {
  std::vector<float> id_1_data = {1, 0, 0, 0, 0, 1, 0, 0,
                                  0, 0, 1, 0, 0, 0, 0, 1};
  Matrix id_1(id_1_data);

  EXPECT_EQ(id_1, id_1.inverse());
}

// Scenario: The inverse of the transpose equals the transpose of the inverse
// p42
TEST(TestMatrices, InverseAndTranspose) {
  std::vector<float> a_data = {9,  3, 0, 9, -5, -2, -6, -3,
                               -4, 9, 6, 4, -7, 6,  6,  2};
  Matrix a(a_data);

  EXPECT_EQ(a.inverse().transpose(), a.transpose().inverse());
}
