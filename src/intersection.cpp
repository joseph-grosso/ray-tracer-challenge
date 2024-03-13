#include <vector>
#include "intersection.h"
#include "sphere.h"
#include "ray.h"


Intersection::Intersection(float t, Sphere obj) {
    this->t = t;
    this->object = obj;
};

Intersections::Intersections() {
    this->data = std::vector<Intersection>{};
    this->count = 0;
};

Intersections::Intersections(std::vector<Intersection> data) {
    this->data = data;
    this->count = data.size();
};

Intersection Intersections::operator[](int i) {
    return data[i];
};

Intersections intersect(Sphere s, Ray r) {
    // the vector form the sphere's center to the ray origin
    // Remember: the sphere is centered at the world origin
    Tuple sphere_to_ray = r.get_origin() - point(0, 0, 0);
    float a = r.get_direction().dot(r.get_direction());
    float b = 2 * r.get_direction().dot(sphere_to_ray);
    float c = sphere_to_ray.dot(sphere_to_ray) - 1;

    float discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        // No intersection, return Intersection of len 0
        return Intersections();
    };
    // At least 1 intersection
    return Intersections(std::vector<Intersection>{
        Intersection((-b - std::sqrt(discriminant)) / (2 * a), s.copy()),
        Intersection((-b + std::sqrt(discriminant)) / (2 * a), s.copy())
    });
};
