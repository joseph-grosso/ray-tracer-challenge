#pragma once

#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"


// Chapter 7: Building a World
class Computation {
    public:
        // Attributes
        float t;
        Sphere * object;
        Tuple point;
        Tuple over_point;
        Tuple eyev;
        Tuple normalv;
        bool inside;
        Computation(float t, Sphere * object, Tuple point, Tuple eyev, Tuple normalv);
};

Computation prepare_computations(Intersection i, Ray r);
