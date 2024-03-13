#pragma once

#include "tuple.h"
#include "matrix.h"


// Chapter 5: Rays
class Sphere {
    private:
        Tuple center;
        float radius;
    public:
        // Methods
        Sphere(Tuple center = point(0, 0, 0), float radius = 1.0);
        Tuple get_center();
        float get_radius();
};

