#pragma once

#include <vector>
#include "ray.h"
#include "intersection.h"


class Intersections {
    public:
        Intersections() : Intersections(std::vector<Intersection>{}) {};
        Intersections(std::vector<Intersection>);
        std::vector<Intersection> data;
        int count;
        Intersection operator[](int);
        Intersection hit();
};
