#pragma once

#include "tuple.h"
#include <vector>
#include <string>


// Chapter 3: Matrix Math
class Matrix {
    private:
        unsigned int rows_;
        unsigned int columns_;
        std::vector<float> data_;
        void check_valid_row_coord(unsigned int row_coord);
        void check_valid_column_coord(unsigned int column_coord);
        Matrix cofactor_matrix();
    public:
        // Methods
        Matrix(
            unsigned int rows = 4,
            unsigned int columns = 4,
            std::vector<float> data = std::vector<float> {1, 0, 0, 0,
                                                          0, 1, 0, 0,
                                                          0, 0, 1, 0,
                                                          0, 0, 0, 1});
        float get_point(unsigned int row, unsigned int col);
        std::vector<float> get_row(unsigned int row);
        std::vector<float> get_column(unsigned int col);
        unsigned int get_row_count();
        unsigned int get_column_count();
        unsigned int get_elements_count();
        std::vector<float> get_matrix_data();
        Matrix transpose();
        float determinant();
        float minor(unsigned int row, unsigned int col);
        Matrix submatrix(unsigned int row, unsigned int col);
        float cofactor(unsigned int row, unsigned int col);
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
Matrix identity_matrix(int size);
