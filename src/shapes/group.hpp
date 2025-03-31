#pragma once

#include <bits/stdc++.h>

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
  Group(Matrix t, std::vector<Shape *> children = std::vector<Shape *>{})
      : Shape(t) {
    this->children = children;
  };
  Group(std::vector<Shape *> children = std::vector<Shape *>{})
      : Shape(identity_matrix()) {
    this->children = children;
  };
  int get_count() { return children.size(); };
  int is_empty() { return children.size() == 0; };
  void add_child(Shape *s) {
    children.push_back(s);
    s->parent = this;
  };
  void set_all_materials(Material m);
  int get_number_of_children() { return children.size(); };
  Shape *get_child(int i) { return children[i]; };
  Tuple local_normal_at(float x, float y, float z);
  Tuple local_normal_at(Tuple p, Intersection i = Intersection());
  std::string to_string();
  Intersections local_intersect(Ray r);
  bool includes(Shape *target) override {
    for (auto i : children) {
      if (i->includes(target)) {
        return true;
      };
    };
    return false;
  };
};
