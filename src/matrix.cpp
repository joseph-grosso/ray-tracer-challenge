#include "matrix.hpp"

// Chapter 3: Matrix Math
Matrix::Matrix(std::vector<float> data) {
  if (16 != data.size()) {
    throw std::invalid_argument("Input data must have 16 values.");
  };
  _eigen_data = Eigen::Map<Eigen::Matrix<float, 4, 4, Eigen::RowMajor>>(
      data.data(), 4, 4);
};

Matrix::Matrix(Eigen::Matrix4f eigen_data) { _eigen_data = eigen_data; };

// Matrix(unsigned int rows, unsigned int columns, float data[]);
float Matrix::get_point(unsigned int row, unsigned int col) {
  // TODO: Add a try-catch block to handle out of range errors?
  return _eigen_data(row, col);
};

std::vector<float> Matrix::get_row(unsigned int row) {
  // TODO: Add a try-catch block to handle out of range errors?
  Eigen::VectorXf eigen_row = _eigen_data.row(row);
  return std::vector<float>(eigen_row.data(),
                            eigen_row.data() + eigen_row.size());
};

std::vector<float> Matrix::get_column(unsigned int col) {
  Eigen::VectorXf eigen_col = _eigen_data.col(col);
  return std::vector<float>(eigen_col.data(),
                            eigen_col.data() + eigen_col.size());
};

Eigen::Matrix4f Matrix::get_eigen_data() { return _eigen_data; };

unsigned int Matrix::get_row_count() { return _eigen_data.rows(); };

unsigned int Matrix::get_column_count() { return _eigen_data.cols(); };

// Arithmetic operator overloads
bool operator==(Matrix lhs, Matrix rhs) {
  return lhs.get_eigen_data().isApprox(rhs.get_eigen_data(), 1e-4);
};

bool operator!=(Matrix lhs, Matrix rhs) { return !operator==(lhs, rhs); };

Matrix operator*(Matrix lhs, Matrix rhs) {
  Eigen::MatrixXf lhs_mat = lhs.get_eigen_data();
  Eigen::MatrixXf rhs_mat = rhs.get_eigen_data();
  return Matrix(lhs_mat * rhs_mat);
};

Tuple operator*(Matrix m, Tuple t) {
  return Tuple(m.get_eigen_data() * t.values);
};

Matrix operator*(Matrix m, float x) { return Matrix(m.get_eigen_data() * x); };

float dot_product(std::vector<float> v1, std::vector<float> v2) {
  if (v1.size() != v2.size()) {
    throw std::invalid_argument(
        "Length of vector 1 does not match length of vector 2");
  };
  return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
};

// TODO: Remove once you're done debugging tests.
template <typename S>
std::ostream &operator<<(std::ostream &os, const std::vector<S> &vector) {
  // Printing all the elements
  // using <<
  for (auto element : vector) {
    os << element << " ";
  }
  return os;
};

Matrix Matrix::transpose() { return Matrix(_eigen_data.transpose()); };

Matrix Matrix::inverse() { return Matrix(_eigen_data.inverse()); };

float Matrix::determinant() {
  if (!is_square()) {
    throw std::invalid_argument("Row coordinate out of range of matrix");
  };

  return _eigen_data.determinant();
};

bool Matrix::is_square() { return _eigen_data.rows() == _eigen_data.cols(); };

bool Matrix::is_invertible() { return !equalByEpsilon(determinant(), 0); };

std::string Matrix::to_string() {
  std::stringstream ss;
  ss << _eigen_data;
  return ss.str();
};

unsigned int Matrix::get_elements_count() {
  return _eigen_data.rows() * _eigen_data.cols();
};

Matrix identity_matrix(int size) {
  return Matrix(Eigen::Matrix4f::Identity());
};

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Matrix &m, std::ostream *os) {
  Matrix &ref = const_cast<Matrix &>(m);
  *os << ref.to_string();
}
