#include "tuple.h"
#include "sphere.h"
#include "ray.h"
#include "matrix.h"
#include "material.h"

#include <stdexcept>
#include <cmath>
#include <random> 
#include <vector>

// TODO: Add a to_string function that adds this info.
#include <iostream>
#include <chrono>

static std::random_device rd;

Sphere::Sphere() {
    this->center = point(0, 0, 0);
    this->radius = 1.0;
    this->transformation = Matrix();
    this->material = Material();
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
