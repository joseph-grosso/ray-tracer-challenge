#include "matrix.hpp"

// Chapter 3: Matrix Math
Matrix::Matrix(unsigned int rows, unsigned int columns,
               std::vector<float> data) {
  if (rows * columns != data.size()) {
    throw std::invalid_argument(
        "rows * columns must equal the size of input data.");
  };
  rows_ = rows;
  columns_ = columns;
  _eigen_data = Eigen::Map<
      Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(
      data.data(), rows_, columns_);
};

Matrix::Matrix(Eigen::MatrixXf eigen_data) {
  rows_ = eigen_data.rows();
  columns_ = eigen_data.cols();
  _eigen_data = eigen_data;
};

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

Eigen::MatrixXf Matrix::get_eigen_data() { return _eigen_data; };

unsigned int Matrix::get_row_count() { return rows_; };

unsigned int Matrix::get_column_count() { return columns_; };

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
  if (m.get_row_count() != 4 || m.get_column_count() != 4) {
    throw std::invalid_argument(
        "Unfit matrix: Matrix must be 4x4 to multiply with a tuple.");
  };
  std::vector<float> tup_as_vector = {t.x, t.y, t.z, t.w};
  return Tuple(dot_product(m.get_row(0), tup_as_vector),
               dot_product(m.get_row(1), tup_as_vector),
               dot_product(m.get_row(2), tup_as_vector),
               dot_product(m.get_row(3), tup_as_vector));
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

bool Matrix::is_square() { return rows_ == columns_; };

bool Matrix::is_invertible() { return !equalByEpsilon(determinant(), 0); };

std::string Matrix::to_string() {
  std::stringstream ss;
  ss << _eigen_data;
  return ss.str();
};

unsigned int Matrix::get_elements_count() { return rows_ * columns_; };

Matrix identity_matrix(int size) {
  return Matrix(Eigen::MatrixXf::Identity(size, size));
};

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Matrix &m, std::ostream *os) {
  Matrix &ref = const_cast<Matrix &>(m);
  *os << ref.to_string();
}
