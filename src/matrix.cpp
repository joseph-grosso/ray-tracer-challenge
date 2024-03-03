#include "tuple.h"
#include "matrix.h"
#include <vector>

#include <stdexcept>


// Chapter 3: Matrix Math
Matrix::Matrix(unsigned int rows, unsigned int columns, std::vector<float> data) {
    if (rows * columns != data.size()) {
        throw std::invalid_argument("rows * columns must equal the size of input data.");
    };
    rows_ = rows;
    columns_ = columns;
    data_ = data;
}

// Matrix(unsigned int rows, unsigned int columns, float data[]);
float Matrix::get_point(unsigned int row, unsigned int col) {
    return data_[row * columns_ + col];
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


bool operator==(Matrix lhs, Matrix rhs) {
    if (lhs.get_row_count() != rhs.get_row_count() || lhs.get_column_count() != rhs.get_column_count()) {
        return false;
    };
    return lhs.get_matrix_data() == rhs.get_matrix_data();
};

bool operator!=(Matrix lhs, Matrix rhs) {
    return !operator==(lhs, rhs);
};
