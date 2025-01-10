#pragma once

#include <string>
#include <vector>

#include "intersection.hpp"
#include "intersections.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "tuple.hpp"

// Chapter 14: Groups
class Group : public Shape {
 private:
  std::vector<Shape *> children;

 public:
  // Methods
  Group(Matrix t = identity_matrix(4),
        std::vector<Shape *> children = std::vector<Shape *>{})
      : Shape(t) {
    this->children = children;
  };
  int get_count() { return children.size(); };
  int is_empty() { return children.size() == 0; };
  void add_child(Shape *s) {
    children.push_back(s);
    s->parent = this;
  };
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p);
  std::string to_string();
  Intersections local_intersect(Ray r);
};
