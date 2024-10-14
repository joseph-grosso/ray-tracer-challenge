#pragma once

#include "tuple.h"
#include "matrix.h"
#include "color.h"

#include <cmath>

class Shape;

class Pattern {
    private:
        Matrix transform;
    public:
        Pattern(Matrix t);
        void set_transform(Matrix t);
        Matrix get_transform();
        virtual Color pattern_at(Tuple p) = 0;  // must be a point, not vector
        Color pattern_at_shape(Shape * object, Tuple point_);
};
