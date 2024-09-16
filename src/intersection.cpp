#include <vector>
#include <stdexcept>

#include "intersection.h"
#include "sphere.h"
#include "ray.h"



Intersection::Intersection() {
    this->empty = true;
};

Intersection::Intersection(float t, Sphere *const obj) {
    this->t = t;
    this->object = obj;
    this->empty = false;
};

bool Intersection::is_empty() {
    return empty;
};

bool operator==(Intersection lhs, Intersection rhs) {
    return (
        lhs.object == rhs.object &&
        lhs.t == rhs.t
    );
};

bool operator<(Intersection lhs, Intersection rhs) {
    return lhs.t < rhs.t;
};

Computation Intersection::prepare_computations(Ray r) {
    Tuple point = r.position(t);
    Tuple eyev = -r.get_direction();
    Tuple normalv = (*object).normal_at(point);

    return Computation(t, object, point, eyev, normalv);
};
