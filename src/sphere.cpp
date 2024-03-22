#include "tuple.h"
#include "sphere.h"
#include "ray.h"
#include "matrix.h"
#include "material.h"

#include <stdexcept>
#include <cmath>
#include <random> 
#include <vector>

// TODO: remove after testing
#include <iostream>


Sphere::Sphere(Tuple center, float radius) {
    if (!center.isPoint()) {
        throw std::invalid_argument("The center passed in must be a Point.");
    };

    this->center = center;
    this->radius = radius;
    std::random_device rd;
    this->random_id = rd();
    this->transformation = Matrix();
    this->material = Material();
};

Tuple Sphere::get_center() {
    return center;
};

float Sphere::get_radius() {
    return radius;
};

int Sphere::get_random_id() {
    return random_id;
};

Sphere Sphere::copy() {
    Sphere copy_s(center, radius, random_id);
    copy_s.set_material(material);
    return copy_s;
};

Sphere::Sphere(Tuple center, float radius, int set_random_id) {
    this->center = center;
    this->radius = radius;
    // TODO: Consider other options for assigning random id.
    int random_id = set_random_id;
};


bool operator==(Sphere lhs, Sphere rhs) {
    return (
        lhs.get_center() == rhs.get_center() &&
        lhs.get_radius() == rhs.get_radius() &&
        // TODO: Update when IDs are updated
        lhs.get_random_id() == rhs.get_random_id() // &&
        // lhs.get_transform() == rhs.get_transform()
    );
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
