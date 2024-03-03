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
