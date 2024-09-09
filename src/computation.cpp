#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"
#include "computation.h"


// Chapter 7: Building a World
Computation::Computation(float t, Sphere object, Tuple point, Tuple eyev, Tuple normalv) {
        this->t = t;
        this->object = object;
        this->point = point;
        this->eyev = eyev;
        if (normalv.dot(eyev) < 0) {
            this->inside = true;
            this->normalv = -normalv;
        } else {
            this->inside = false;
            this->normalv = normalv;
        };
        // TODO: Create epsilon constant that is shared around the codebase
        // TODO: Fix the shading function to 
        // * make epsilon here smaller
        // * Reduce acne when epsilon is smaller
        this->over_point = this->point + this->normalv * 0.002;  // EPSILON
};

Computation prepare_computations(Intersection i, Ray r) {
    Tuple point = r.position(i.t);
    Tuple eyev = -r.get_direction();
    Sphere obj = *(i.object);
    Tuple normalv = obj.normal_at(point);

    return Computation(i.t, obj, point, eyev, normalv);
};
