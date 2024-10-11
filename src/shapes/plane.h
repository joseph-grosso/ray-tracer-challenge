#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"
#include "intersections.h"
#include "shape.h"

#include <vector>
#include <random> 
#include <string>
#include <cmath>


// Chapter 9: Planes
class Plane : public Shape {
    private:
        Tuple normal;
        Tuple point_inside;
    public:
        // Methods
        Plane(Matrix t = identity_matrix(4), Material m = Material()) : Shape(t, m) {
            this->normal = vector(0, 1, 0);
            this->point_inside = point(0, 0, 0);
        };
        Tuple local_normal_at(float x, float y, float z);
        Tuple local_normal_at(Tuple p);
        // TODO: refactor when an intersection is done on a general "object" class
        // rather than just the sphere class.
        Intersections local_intersect(Ray r);
};

// bool operator==(Plane lhs, Plane rhs);
// bool operator!=(Plane lhs, Plane rhs);
