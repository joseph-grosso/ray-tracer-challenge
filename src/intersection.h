#pragma once

#include <vector>
#include "sphere.h"
#include "ray.h"

class Intersection {
    private:
        bool empty;
    public:
        Intersection();
        Intersection(float t, Sphere obj);
        float t;
        // TODO: use OOP to generalize this object class
        Sphere object;
        bool is_empty();
};

class Intersections {
    public:
        Intersections() : Intersections(std::vector<Intersection>{}) {};
        Intersections(std::vector<Intersection>);
        std::vector<Intersection> data;
        int count;
        Intersection operator[](int);
        Intersection hit();
};

// TODO: refactor when an intersection is done on a general "object" class
// rather than just the sphere class. 
Intersections intersect(Sphere s, Ray r);

bool operator==(Intersection lhs, Intersection rhs);
bool operator<(Intersection lhs, Intersection rhs);
