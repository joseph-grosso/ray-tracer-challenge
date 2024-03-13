#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"

#include <vector>
#include <random> 


// Chapter 5: Rays
class Sphere {
    private:
        Tuple center;
        float radius;
        // TODO: Consider other options for assigning random id.
        int random_id;
    public:
        // Methods
        Sphere(Tuple center = point(0, 0, 0), float radius = 1.0);
        Sphere(Tuple center, float radius, int set_random_id);
        Tuple get_center();
        float get_radius();
        int get_random_id();
        Sphere copy();
};

bool operator==(Sphere lhs, Sphere rhs);
