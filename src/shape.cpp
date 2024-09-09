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
