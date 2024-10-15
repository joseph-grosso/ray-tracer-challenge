#include <cmath>

#include "gtest/gtest.h"
#include "tuple.hpp"

// Scenario: A tuple with w=1.0 is a point
// page 4
TEST(TestTuples, TupleDesign) {
  Tuple a(4.3, -4.2, 3.1, 1.0);
  EXPECT_TRUE(equalByEpsilon(a.x, 4.3));
  EXPECT_TRUE(equalByEpsilon(a.y, -4.2));
  EXPECT_TRUE(equalByEpsilon(a.z, 3.1));
  EXPECT_TRUE(equalByEpsilon(a.w, 1.0));
  EXPECT_TRUE(a.isPoint());
  EXPECT_TRUE(!a.isVector());
};

// Scenario: A tuple with w=0 is a vector
// page 4
TEST(TestTuples, VectorDesign) {
  Tuple b(4.3, -4.2, 3.1, 0.0);
  EXPECT_TRUE(equalByEpsilon(b.x, 4.3));
  EXPECT_TRUE(equalByEpsilon(b.y, -4.2));
  EXPECT_TRUE(equalByEpsilon(b.z, 3.1));
  EXPECT_TRUE(equalByEpsilon(b.w, 0));
  EXPECT_TRUE(!b.isPoint());
  EXPECT_TRUE(b.isVector());
};

// Scenario: point() creates tuples with w=1
// p4
TEST(TestTuples, PointFunction) {
  Tuple p = point(4, -4, 3);
  Tuple expected_point = Tuple(4, -4, 3, 1);
  EXPECT_TRUE(expected_point == p);
};

// Scenario: vector() creates tuples with w=0
// p4
TEST(TestTuples, VectorFunction) {
  Tuple v = vector(4, -4, 3);
  Tuple expected_vector = Tuple(4, -4, 3, 0);
  EXPECT_TRUE(expected_vector == v);
}

// Scenario: Adding two tuples
// p6
TEST(TestTuples, AddingTuples) {
  Tuple a1(3, -2, 5, 1);
  Tuple a2(-2, 3, 1, 0);
  Tuple actual = a1 + a2;
  Tuple expected(1, 1, 6, 1);
  EXPECT_TRUE(expected == actual);
}

// Scenario: Subtracting two points
// p6
TEST(TestTuples, SubtractingPoints) {
  Tuple b1 = point(3, 2, 1);
  Tuple b2 = point(5, 6, 7);
  Tuple actual_2 = b1 - b2;
  Tuple expected_2 = vector(-2, -4, -6);
  EXPECT_TRUE(expected_2 == actual_2);
}

// Scenario: Subtracting a vector from a point
// p6
TEST(TestTuples, SubtractingVectorFromPoint) {
  Tuple p1 = point(3, 2, 1);
  Tuple v1 = vector(5, 6, 7);
  Tuple actual_3 = p1 - v1;
  Tuple expected_3 = point(-2, -4, -6);
  EXPECT_TRUE(actual_3 == expected_3);
}

// Scenario: Subtracting two vectors
// p7
TEST(TestTuples, SubtractingVectors) {
  Tuple v_1 = vector(3, 2, 1);
  Tuple v_2 = vector(5, 6, 7);
  Tuple actual_4 = v_1 - v_2;
  Tuple expected_4 = vector(-2, -4, -6);
  EXPECT_TRUE(actual_4 == expected_4);
}

// Scenario: Subtracting a vector from the zero vector
// p7
TEST(TestTuples, SubtractingZeroVector) {
  Tuple zero = vector(0, 0, 0);
  Tuple v_3 = vector(1, -2, 3);
  Tuple actual_5 = zero - v_3;
  Tuple expected_5 = vector(-1, 2, -3);
  EXPECT_TRUE(actual_5 == expected_5);
}

// Scenario: Negating a tuple
// p7
TEST(TestTuples, NegatingTuple) {
  Tuple a3(1, -2, 3, -4);
  Tuple actual_6 = -a3;
  Tuple expected_6(-1, 2, -3, 4);
  EXPECT_TRUE(actual_6 == expected_6);
}

// Scenario: Multiplying a tuple by a scalar
// p8
TEST(TestTuples, MultiplyTupleByScalar) {
  Tuple a4(1, -2, 3, -4);
  Tuple actual_7 = a4 * 3.5f;
  Tuple expected_7(3.5, -7, 10.5, -14);
  EXPECT_TRUE(actual_7 == expected_7);
}

// Scenario: Multiplying a tuple by a scalar part 2
// p8
TEST(TestTuples, MultiplyTupleByFractionalScalar) {
  Tuple a5(1, -2, 3, -4);
  Tuple actual_8 = 0.5f * a5;
  Tuple expected_8(0.5, -1, 1.5, -2);
  EXPECT_TRUE(actual_8 == expected_8);
}

// Scenario: Dividing a tuple by a scalar
// p8
TEST(TestTuples, DivideTupleByScalar) {
  Tuple a6(1, -2, 3, -4);
  Tuple actual_9 = a6 / 2.0f;
  Tuple expected_9(0.5, -1, 1.5, -2);
  EXPECT_TRUE(actual_9 == expected_9);
}

// Scenario: Computing the magnitude of vector(1, 0, 0)
// p8
TEST(TestTuples, ComputeMagnitude_1) {
  Tuple vec_1 = vector(1, 0, 0);
  EXPECT_TRUE(equalByEpsilon(vec_1.magnitude(), 1));
}

// Scenario: Computing the magnitude of vector(0, 1, 0)
// p9
TEST(TestTuples, ComputeMagnitude_2) {
  Tuple vec_2 = vector(0, 1, 0);
  EXPECT_TRUE(equalByEpsilon(vec_2.magnitude(), 1));
}

// Scenario: Computing the magnitude of vector(0, 0, 1)
// p9
TEST(TestTuples, ComputeMagnitude_3) {
  Tuple vec_3 = vector(0, 0, 1);
  EXPECT_TRUE(equalByEpsilon(vec_3.magnitude(), 1));
}

// Scenario: Computing the magnitude of vector(1, 2, 3)
// p9
TEST(TestTuples, ComputeMagnitude_4) {
  Tuple vec_4 = vector(1, 2, 3);
  EXPECT_TRUE(equalByEpsilon(vec_4.magnitude(), sqrt(14)));
}

// Scenario: Computing the magnitude of vector(-1, -2, -3)
// p9
TEST(TestTuples, ComputeMagnitude_5) {
  Tuple vec_5 = vector(-1, -2, -3);
  EXPECT_TRUE(equalByEpsilon(vec_5.magnitude(), sqrt(14)));
}

// Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)
// p10
TEST(TestTuples, Normalization_1) {
  Tuple vec_6 = vector(4, 0, 0);
  Tuple expected_10 = vector(1, 0, 0);
  EXPECT_TRUE(vec_6.normalize() == expected_10);
}

// Scenario: Normalizing vector(1, 2, 3)
// p10
TEST(TestTuples, Normalization_2) {
  Tuple vec_7 = vector(1, 2, 3);
  Tuple expected_11 = vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
  EXPECT_TRUE(vec_7.normalize() == expected_11);
}

// Scenario: The magnitude of a normalized vector
// p10
TEST(TestTuples, Normalization_3) {
  Tuple vec_8 = vector(1, 2, 3);
  EXPECT_TRUE(equalByEpsilon(vec_8.normalize().magnitude(), 1));
}

// Scenario: The dot product of two tuples
// p10
TEST(TestTuples, DotProductOfTuples) {
  Tuple a7 = vector(1, 2, 3);
  Tuple b7 = vector(2, 3, 4);
  EXPECT_TRUE(20 == a7.dot(b7));
}

// Scenario: The cross product of unit tuples
// p11
TEST(TestTuples, CrossProductOfUnitTuples) {
  Tuple x = vector(1, 0, 0);
  Tuple y = vector(0, 1, 0);
  Tuple z = vector(0, 0, 1);
  EXPECT_TRUE(x.cross(y) == z);
  EXPECT_TRUE(y.cross(x) == -z);
}

// Scenario: The cross product of two tuples
// p11
TEST(TestTuples, CrossProductOfRandomTuples) {
  Tuple a8 = vector(1, 2, 3);
  Tuple b8 = vector(2, 3, 4);
  EXPECT_TRUE(vector(-1, 2, -1) == a8.cross(b8));
  EXPECT_TRUE(vector(1, -2, 1) == b8.cross(a8));
}