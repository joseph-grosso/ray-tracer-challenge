#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "intersection.h"
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

Intersection Ray::intersect(Sphere s) {
    // the vector form the sphere's center to the ray origin
    // Remember: the sphere is centered at the world origin
    Tuple sphere_to_ray = origin - point(0, 0, 0);
    float a = direction.dot(direction);
    float b = 2 * direction.dot(sphere_to_ray);
    float c = sphere_to_ray.dot(sphere_to_ray) - 1;

    float discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        // No intersection, return Intersection of len 0
        return Intersection(std::vector<float>{});
    };
    std::vector<float> intersection_data = {
        (-b - std::sqrt(discriminant)) / (2 * a),
        (-b + std::sqrt(discriminant)) / (2 * a)        
    };
    // At least 1 intersection
    return Intersection(intersection_data);
};
