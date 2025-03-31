#include "shape.hpp"

#include <random>
#include <string>
#include <vector>

#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"

// Chapter 9: Shapes and Planes
Shape::Shape(Matrix t, Material m, bool throws_shadow, Shape* parent) {
  std::cout << "Shape constructor called." << std::endl;
  this->transformation = t;
  std::cout << "Transform end." << std::endl;
  this->inverse_transformation = t.inverse();
  std::cout << "inverse completed." << std::endl;
  this->material = m;
  this->throws_shadow = throws_shadow;
  this->parent = parent;
  std::cout << "Shape constructor end." << std::endl;
};

Matrix Shape::get_transform() { return transformation; };

void Shape::set_transform(Matrix m) {
  this->transformation = m;
  inverse_transformation = m.inverse();
};

Material Shape::get_material() { return material; };

void Shape::set_material(Material m) { this->material = m; };

Intersections Shape::intersect(Ray r) {
  Ray local_ray = r.transform(inverse_transformation);
  return local_intersect(local_ray);
};

// page 120 AND page 200 of RTC
Tuple Shape::normal_at(Tuple world_point, Intersection i) {
  Tuple local_point = world_to_object(world_point);
  Tuple local_normal = local_normal_at(local_point, i);

  return normal_to_world(local_normal);
};

Tuple Shape::normal_at(float x, float y, float z) {
  return normal_at(point(x, y, z));
};

void Shape::set_throws_shadow(bool throws_shadow) {
  this->throws_shadow = throws_shadow;
}

bool Shape::get_throws_shadow() { return throws_shadow; }

Tuple Shape::world_to_object(Tuple p) {
  Tuple point_ = (parent != nullptr) ? parent->world_to_object(p) : p;

  return inverse_transformation * point_;
};

Tuple Shape::normal_to_world(Tuple n) {
  Tuple normal = inverse_transformation.transpose() * n;
  Tuple normal_zeroed_w = vector(normal.x(), normal.y(), normal.z());
  normal = normal_zeroed_w.normalize();

  return (parent != nullptr) ? parent->normal_to_world(normal) : normal;
};
