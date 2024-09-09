#include "tuple.h"
#include "sphere.h"
#include "ray.h"
#include "matrix.h"
#include "material.h"
#include "intersection.h"
#include "intersections.h"

#include <stdexcept>
#include <cmath>
#include <random> 
#include <vector>

// TODO: Add a to_string function that adds this info.
#include <iostream>
#include <chrono>

static std::random_device rd;

Sphere::Sphere(Matrix t, Material m) {
    this->center = point(0, 0, 0);
    this->radius = 1.0;
    this->transformation = t;
    this->material = m;
};

Tuple Sphere::get_center() {
    return center;
};

float Sphere::get_radius() {
    return radius;
};

Sphere Sphere::copy() {
    Sphere copy_s;
    copy_s.set_material(material);
    copy_s.set_transform(transformation);
    return copy_s;
};

bool operator==(Sphere lhs, Sphere rhs) {
    return (
        lhs.get_center() == rhs.get_center() &&
        equalByEpsilon(lhs.get_radius(), rhs.get_radius()) &&
        lhs.get_transform() == rhs.get_transform() &&
        lhs.get_material() == rhs.get_material()
    );
};

bool operator!=(Sphere lhs, Sphere rhs) {
    return !(lhs == rhs);
};


Matrix Sphere::get_transform() {
    return transformation;
};

void Sphere::set_transform(Matrix m) {
    if (m.get_row_count() != 4 || m.get_column_count() != 4) {
        throw std::invalid_argument("Unfit matrix: Matrix must be 4x4 to be a transformation on an object.");
    };
    this->transformation = m;
};

// chapter 6: Lighting and Shading
Tuple Sphere::normal_at(float x, float y, float z) {
    // Algorithm explanation: p80 - p82
    Tuple world_point = point(x, y, z);
    Tuple obj_point = transformation.inverse() * world_point;
    Tuple obj_normal = obj_point - point(0, 0, 0);
    Tuple world_normal = transformation.inverse().transpose() * obj_normal;
    world_normal.w = 0;
    return world_normal.normalize();
};

Tuple Sphere::normal_at(Tuple p) {
    return normal_at(p.x, p.y, p.z);
};

Material Sphere::get_material() {
    return material;
};

void Sphere::set_material(Material m) {
    this->material = m;
};

std::string Sphere::to_string() {
    return "\nTransform:\n" + transformation.to_string() +
    "\nMaterial: " + material.to_string();
};

Intersections Sphere::intersect(Ray r) {
    // The ray transformed by the inverse of the object matrix
    Ray r_trans = r.transform(get_transform().inverse());

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
        Intersection((-b - std::sqrt(discriminant)) / (2 * a), this),
        Intersection((-b + std::sqrt(discriminant)) / (2 * a), this)
    });
};