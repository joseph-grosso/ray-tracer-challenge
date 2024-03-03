#pragma once

#include "tuple.h"
#include <vector>


// Chapter 3: Matrix Math
class Matrix {
    private:
        unsigned int rows_;
        unsigned int columns_;
        std::vector<float> data_;
    public:
        // Methods
        Matrix(unsigned int rows, unsigned int columns, std::vector<float> data);
        float get_point(unsigned int row, unsigned int col);
};