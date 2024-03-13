#include "tuple.h"
#include "sphere.h"
#include "ray.h"

#include <stdexcept>
#include <cmath>
#include <random> 


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


// Returns an ordered float vector of the intersections
// between a ray and a sphere.
std::vector<float> Sphere::intersect(Ray r) {
    // the vector form the sphere's center to the ray origin
    // Remember: the sphere is centered at the world origin
    Tuple sphere_to_ray = r.get_origin() - point(0, 0, 0);
    float a = r.get_direction().dot(r.get_direction());
    float b = 2 * r.get_direction().dot(sphere_to_ray);
    float c = sphere_to_ray.dot(sphere_to_ray) - 1;

    float discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        // No intersection, return Intersection of len 0
        return std::vector<float>{};
    };
    // At least 1 intersection
    return std::vector<float>{
        (-b - std::sqrt(discriminant)) / (2 * a),
        (-b + std::sqrt(discriminant)) / (2 * a)        
    };
};

int Sphere::get_random_id() {
    return random_id;
};

bool operator==(Sphere lhs, Sphere rhs) {
    return (
        lhs.get_center() == rhs.get_center() &&
        lhs.get_radius() == rhs.get_radius() &&
        // TODO: Update when IDs are updated
        lhs.get_random_id() == rhs.get_random_id()
    );
};
