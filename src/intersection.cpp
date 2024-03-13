#include <vector>
#include "intersection.h"


Intersection::Intersection(float t, Sphere obj) {
    this->t = t;
    this->object = obj;
};

Intersections::Intersections(std::vector<Intersection> data) {
    this->data = data;
    this->count = data.size();
};

Intersection Intersections::operator[](int i) {
    return data[i];
};
