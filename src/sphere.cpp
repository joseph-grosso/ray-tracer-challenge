#include "tuple.h"
#include "sphere.h"
#include "ray.h"
#include "matrix.h"

#include <stdexcept>
#include <cmath>
#include <random> 
#include <vector>


Sphere::Sphere(Tuple center, float radius) {
    if (!center.isPoint()) {
        throw std::invalid_argument("The center passed in must be a Point.");
    };

    this->center = center;
    this->radius = radius;
    std::random_device rd;
    this->random_id = rd();
    this->transformation = Matrix();
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
    return Sphere(center, radius, random_id);
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