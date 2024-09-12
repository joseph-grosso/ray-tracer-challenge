#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "intersections.h"

#include "shape.h"

#include <vector>
#include <random> 
#include <string>


// Chapter 9: Shapes and Planes
Shape::Shape(Matrix t, Material m) {
    this->transformation = t;
    this->material = m;
};

Matrix Shape::get_transform() {
    return transformation;
};

void Shape::set_transform(Matrix m) {
    this->transformation = m;
};

Material Shape::get_material() {
    return material;
};

void Shape::set_material(Material m) {
    this->material = m;
};

Intersections Shape::intersect(Ray r) {
    Ray local_ray = r.transform(get_transform().inverse());
    return local_intersect(local_ray);
};

// page 120 of RTC
Tuple Shape::normal_at(Tuple p) {
    Tuple local_point = get_transform().inverse() * p;
    Tuple local_normal = local_normal_at(local_point);
    Tuple world_normal = get_transform().inverse().transpose() * local_normal;
    world_normal.w = 0;

    return world_normal.normalize();
};

Tuple Shape::normal_at(float x, float y, float z) {
    return normal_at(point(x, y, z));
};
