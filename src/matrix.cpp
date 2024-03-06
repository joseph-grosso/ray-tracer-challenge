#include "tuple.h"
#include "matrix.h"
#include <vector>
#include <numeric>
// TODO: remove
#include <iostream>

#include <stdexcept>
#include <algorithm>


// Chapter 3: Matrix Math
Matrix::Matrix(unsigned int rows, unsigned int columns, std::vector<float> data) {
    if (rows * columns != data.size()) {
        throw std::invalid_argument("rows * columns must equal the size of input data.");
    };
    rows_ = rows;
    columns_ = columns;
    data_ = data;
};

// Matrix(unsigned int rows, unsigned int columns, float data[]);
float Matrix::get_point(unsigned int row, unsigned int col) {
    check_valid_row_coord(row);
    check_valid_column_coord(col);
    return data_[row * columns_ + col];
};


std::vector<float> Matrix::get_row(unsigned int row) {
    check_valid_row_coord(row);
    int start_index = row * columns_;
    int end_index = start_index + columns_;
    return std::vector<float>(data_.begin() + start_index, data_.begin() + end_index);
};

std::vector<float> Matrix::get_column(unsigned int col) {
    check_valid_column_coord(col);
    std::vector<float> col_vector;
    for (int i=0;i<data_.size();i++) {
        if ((i % columns_) == col) {
            col_vector.push_back(data_[i]);
        };
    };
    return col_vector;
};


unsigned int Matrix::get_row_count() {
    return rows_;
};

unsigned int Matrix::get_column_count() {
    return columns_;
};

std::vector<float> Matrix::get_matrix_data() {
    std::vector<float> copy = data_;
    return copy;
};

// Arithmetic operator overloads
bool operator==(Matrix lhs, Matrix rhs) {
    if (lhs.get_row_count() != rhs.get_row_count() || lhs.get_column_count() != rhs.get_column_count()) {
        return false;
    };
    return lhs.get_matrix_data() == rhs.get_matrix_data();
};

bool operator!=(Matrix lhs, Matrix rhs) {
    return !operator==(lhs, rhs);
};

Matrix operator*(Matrix lhs, Matrix rhs) {
    unsigned int new_rows = lhs.get_row_count();
    unsigned int new_cols = rhs.get_column_count();
    std::vector<float> new_data;
    for (int i=0; i<new_rows; i++) {
        for (int j=0; j<new_cols; j++) {
            new_data.push_back(
                // TODO: Find if there's a better way to use this other than a static method.
                dot_product(lhs.get_row(i), rhs.get_column(j))
            );
        };
    };

    return Matrix(new_rows, new_cols, new_data);
};

Tuple operator*(Matrix m, Tuple t) {
    if (m.get_row_count() != 4 || m.get_column_count() != 4) {
        throw std::invalid_argument("Unfit matrix: Matrix must be 4x4 to multiply with a tuple.");
    };
    std::vector<float> tup_as_vector = {t.x, t.y, t.z, t.w};
    return Tuple(
        dot_product(m.get_row(0), tup_as_vector), 
        dot_product(m.get_row(1), tup_as_vector), 
        dot_product(m.get_row(2), tup_as_vector), 
        dot_product(m.get_row(3), tup_as_vector)
    );
};


float dot_product(std::vector<float> v1, std::vector<float> v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("Length of vector 1 does not match length of vector 2");
    };
    return std::inner_product(
        v1.begin(),
        v1.end(),
        v2.begin(),
        0
    );
};

void Matrix::check_valid_row_coord(unsigned int row_coord) {
    if (row_coord >= rows_) {
        throw std::invalid_argument("Row coordinate out of range of matrix");
    };
    return;
};

void Matrix::check_valid_column_coord(unsigned int column_coord) {
    if (column_coord >= columns_) {
        throw std::invalid_argument("Column coordinate out of range of matrix");
    };
    return;
};

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
};


Matrix Matrix::transpose() {
    std::vector<float> new_data;
    std::vector<float> current_col;
    for (int i = 0;i < columns_; i++) {
        current_col = get_column(i);
        std::copy(
            current_col.begin(),
            current_col.end(),
            std::back_inserter(new_data)
        );
    };
    return Matrix(columns_, rows_, new_data);
};



float Matrix::determinant() {
    if (!is_square()) {
        throw std::invalid_argument("Row coordinate out of range of matrix");
    };
    float det = 0;

    if (get_column_count() == 2 && get_row_count() == 2) {
        return get_point(0, 0) * get_point(1, 1)
             - get_point(0, 1) * get_point(1, 0);
    };

    for (int i=0; i<columns_; i++) {
        det += get_point(0, i) * cofactor(0, i);
    };
    return det;
};

float Matrix::minor(unsigned int row, unsigned int col) {
    return submatrix(row, col).determinant();
};

float Matrix::cofactor(unsigned int row, unsigned int col) {
    return (row + col % 2 == 1) ? -minor(row, col) : minor(row, col);
};

Matrix Matrix::submatrix(unsigned int row, unsigned int col) {
    std::vector<float> new_data;
    for (int i=0; i < rows_; i++) {
        for (int j=0; j < columns_; j++) {
            if (i != row && j != col) {
                new_data.push_back(get_point(i, j));
            };
        };
    };
    return Matrix(rows_ - 1, columns_ - 1, new_data);
};

bool Matrix::is_square() {
    return rows_ == columns_;
};

bool Matrix::is_invertible() {
    return determinant() != 0;
};

