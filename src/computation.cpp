#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"
#include "computation.h"


Computation::Computation(float t, Sphere object, Tuple point, Tuple eyev, Tuple normalv) {
        this->t = t;
        this->object = object;
        this->point = point;
        this->eyev = eyev;
        this->normalv = normalv;
};

Computation prepare_computations(Intersection i, Ray r) {
    Tuple point = r.position(i.t);
    Tuple eyev = -r.get_direction();
    Tuple normalv = i.object.normal_at(point);

    return Computation(i.t, i.object, point, eyev, normalv);
};