#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"

#include <vector>
#include <random> 


// Chapter 5: Rays
class Sphere {
    private:
        Tuple center;
        float radius;
        // TODO: Consider other options for assigning random id.
        int random_id;
        Matrix transformation;
        Material material;
    public:
        // Methods
        Sphere();
        Sphere(Tuple center, float radius, int set_random_id);
        Sphere(int set_random_id) : Sphere(point(0, 0, 0), 1, set_random_id) {};
        Tuple get_center();
        float get_radius();
        int get_random_id();
        Sphere copy();
        Matrix get_transform();
        void set_transform(Matrix);
        Material get_material();
        void set_material(Material);
        Tuple normal_at(float x, float y, float z);
        Tuple normal_at(Tuple p);
};

bool operator==(Sphere lhs, Sphere rhs);
