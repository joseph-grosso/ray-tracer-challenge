#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"
#include "intersections.h"

#include <vector>
#include <random> 
#include <string>


// Chapter 5: Rays
class Sphere {
    private:
        Tuple center;
        float radius;
        Matrix transformation;
        Material material;
    public:
        // Methods
        Sphere(Matrix t = identity_matrix(4), Material m = Material());
        // Sphere(Matrix t) : Sphere(t, Material()) {};
        Sphere(Material m) : Sphere(identity_matrix(4), m) {};
        Tuple get_center();
        float get_radius();
        Matrix get_transform();
        void set_transform(Matrix);
        Material get_material();
        void set_material(Material);
        Tuple normal_at(float x, float y, float z);
        Tuple normal_at(Tuple p);
        std::string to_string();
        // TODO: refactor when an intersection is done on a general "object" class
        // rather than just the sphere class.
        Intersections intersect(Ray r);
};

bool operator==(Sphere lhs, Sphere rhs);
bool operator!=(Sphere lhs, Sphere rhs);
