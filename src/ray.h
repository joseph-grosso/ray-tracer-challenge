#pragma once

#include "tuple.h"
#include "matrix.h"

#include <vector>
#include <string>


// Chapter 5: Rays
class Ray {
    private:
        Tuple origin;
        Tuple direction;

    public:
        // Methods
        // TODO: Create a default construction of the Ray class
        Ray(Tuple origin, Tuple direction);
        Tuple get_origin();
        Tuple get_direction();
        Tuple position(float t);
        Ray transform(Matrix m);
};
