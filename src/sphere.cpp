#include "tuple.h"
#include "sphere.h"

#include <stdexcept>


Sphere::Sphere(Tuple center, float radius) {
    if (!center.isPoint()) {
        throw std::invalid_argument("rows * columns must equal the size of input data.");
    };

    this->center = center;
    this->radius = radius;
};

Tuple Sphere::get_center() {
    return center;
};

float Sphere::get_radius() {
    return radius;
};
