#pragma once

#include <vector>
#include "sphere.h"


class Intersection {
    public:
        Intersection(float t, Sphere obj);
        float t;
        // TODO: use OOP to generalize this object class
        Sphere object;
};

class Intersections {
    public:
        Intersections(std::vector<Intersection>);
        std::vector<Intersection> data;
        int count;
        Intersection operator[](int);
};

