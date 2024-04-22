#pragma once

#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"


class Computation {
    public:
        // Attributes
        float t;
        Sphere object;
        Tuple point;
        Tuple eyev;
        Tuple normalv;
        Computation(float t, Sphere object, Tuple point, Tuple eyev, Tuple normalv);
};

Computation prepare_computations(Intersection i, Ray r);
