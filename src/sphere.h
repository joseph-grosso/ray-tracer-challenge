#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"

#include <vector>
#include <random> 
#include <string>


// Chapter 5: Rays
class Sphere {
    private:
        Tuple center;
        float radius;
        // TODO: Consider other options for assigning random id.
        // unsigned int random_id;
        Matrix transformation;
        Material material;
    public:
        unsigned int random_id;
        // Methods
        Sphere();
        Sphere(int determined_id);
        Tuple get_center();
        float get_radius();
        unsigned int get_random_id();
        Sphere copy();
        Matrix get_transform();
        void set_transform(Matrix);
        Material get_material();
        void set_material(Material);
        Tuple normal_at(float x, float y, float z);
        Tuple normal_at(Tuple p);
        std::string to_string();
};

bool operator==(Sphere lhs, Sphere rhs);
