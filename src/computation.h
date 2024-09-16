#pragma once

#include "tuple.h"
#include <vector>

class Sphere;
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
