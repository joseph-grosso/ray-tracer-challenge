#pragma once

#include "tuple.h"
#include <vector>


// Chapter 3: Matrix Math
class Matrix {
    private:
        unsigned int rows_;
        unsigned int columns_;
        std::vector<float> data_;
        void check_valid_row_coord(unsigned int row_coord);
        void check_valid_column_coord(unsigned int column_coord);
    public:
        // Methods
        Matrix(unsigned int rows, unsigned int columns, std::vector<float> data);
        float get_point(unsigned int row, unsigned int col);
        std::vector<float> get_row(unsigned int row);
        std::vector<float> get_column(unsigned int col);
        unsigned int get_row_count();
        unsigned int get_column_count();
        std::vector<float> get_matrix_data();
        Matrix transpose();
        float determinant();
        float minor(unsigned int row, unsigned int col);
        Matrix submatrix(unsigned int row, unsigned int col);
        float cofactor(unsigned int row, unsigned int col);
};

// Arithmetic Operators
bool operator==(Matrix lhs, Matrix rhs);
bool operator!=(Matrix lhs, Matrix rhs);
Matrix operator*(Matrix lhs, Matrix rhs);
Tuple operator*(Matrix m, Tuple t);

// Helpful functions
// TODO: Find if there's a better way to use this 
float dot_product(std::vector<float> v1, std::vector<float> v2);
float determinant(Matrix m);
