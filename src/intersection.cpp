#include <vector>
#include <stdexcept>

#include "intersection.h"
#include "sphere.h"
#include "ray.h"



Intersection::Intersection() {
    this->empty = true;
};

Intersection::Intersection(float t, Sphere obj) {
    this->t = t;
    this->object = obj;
    this->empty = false;
};

Intersections::Intersections(std::vector<Intersection> data) {
    this->data = data;
    this->count = data.size();
};

Intersection Intersections::operator[](int i) {
    return data[i];
};

Intersections intersect(Sphere s, Ray r) {
    // The ray transformed by the inverse of the object matrix
    Ray r_trans = r.transform(s.get_transform().inverse());

    // the vector from the sphere's center to the ray origin
    // Remember: the sphere is centered at the world origin
    Tuple sphere_to_ray = r_trans.get_origin() - point(0, 0, 0);
    float a = r_trans.get_direction().dot(r_trans.get_direction());
    float b = 2 * r_trans.get_direction().dot(sphere_to_ray);
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

bool Intersection::is_empty() {
    return empty;
};


Intersection Intersections::hit() {
    if (count == 0) {
        // TODO: Think about other ways you could avoid throwing this if this causes issues in the future.
        // return null intersection?
        // return Intersection();
        throw std::logic_error("No hits possible - empty list of intersections");
    };
    
    Intersection inter = data[0];

    for (int i=0; i<count; i++) {
        if (data[i].t == 0) {
            return data[i];
        }
        if ((inter.t < 0) ||
            (data[i].t >= 0 && data[i].t < inter.t)) {
            inter = data[i];
        };
    };

    // return the chosen value if valid, if not return empty intersection.
    return (inter.t >= 0) ? inter : Intersection();
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
