#pragma once

#include <eigen3/Eigen/Dense>
#include <numeric>
#include <string>
#include <vector>

#include "tuple.hpp"

// TODO: remove
#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
    MatD;

// Chapter 3: Matrix Math
class Matrix {
 private:
  unsigned int rows_;
  unsigned int columns_;
  Eigen::MatrixXf _eigen_data;

 public:
  // Methods
  Matrix(unsigned int rows = 4, unsigned int columns = 4,
         std::vector<float> data = std::vector<float>{1, 0, 0, 0, 0, 1, 0, 0, 0,
                                                      0, 1, 0, 0, 0, 0, 1});
  Matrix(Eigen::MatrixXf eigen_data);
  float get_point(unsigned int row, unsigned int col);
  std::vector<float> get_row(unsigned int row);
  std::vector<float> get_column(unsigned int col);
  unsigned int get_row_count();
  unsigned int get_column_count();
  unsigned int get_elements_count();
  Eigen::MatrixXf get_eigen_data();
  Matrix transpose();
  float determinant();
  // TODO: Refactor these functions to use Eigen directly
  // float minor(unsigned int row, unsigned int col);
  // Matrix submatrix(unsigned int row, unsigned int col);
  // float cofactor(unsigned int row, unsigned int col);
  // Matrix cofactor_matrix();
  Matrix inverse();
  bool is_square();
  bool is_invertible();
  std::string to_string();
};

// Arithmetic Operators
bool operator==(Matrix lhs, Matrix rhs);
bool operator!=(Matrix lhs, Matrix rhs);
Matrix operator*(Matrix lhs, Matrix rhs);
Tuple operator*(Matrix m, Tuple t);
Matrix operator*(Matrix m, float f);

// Helpful functions
// TODO: Find if there's a better way to use this
float dot_product(std::vector<float> v1, std::vector<float> v2);
Matrix identity_matrix(int size = 4);

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Matrix &m, std::ostream *os);
