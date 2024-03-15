#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>


// Chapter 5: Rays
Ray::Ray(Tuple origin, Tuple direction) {
    if (!origin.isPoint()) {
        throw std::invalid_argument("Origin Error: origin argument must be a point.");
    };
    if (!direction.isVector()) {
        throw std::invalid_argument("Direction Error: direction argument must be a vector.");
    };
    this->origin = origin;
    this->direction = direction;
};

Tuple Ray::get_origin() {
    return origin;
};

Tuple Ray::get_direction() {
    return direction;
};

Tuple Ray::position(float t) {
    return origin + direction * t;
};

Ray Ray::transform(Matrix m) {
    return Ray(m * origin, m * direction);
};
