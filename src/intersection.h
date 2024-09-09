#pragma once

#include <vector>
#include "ray.h"

class Sphere;

class Intersection {
    private:
        bool empty;
    public:
        Intersection();
        Intersection(float t, Sphere *const obj);
        float t;
        // TODO: use OOP to generalize this object class
        Sphere *object;
        bool is_empty();
};

bool operator==(Intersection lhs, Intersection rhs);
bool operator<(Intersection lhs, Intersection rhs);
