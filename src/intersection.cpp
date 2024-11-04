#include "intersection.hpp"

#include <bits/stdc++.h>

#include <stdexcept>
#include <tuple>
#include <vector>

#include "ray.hpp"
#include "sphere.hpp"

Intersection::Intersection() { this->empty = true; };

Intersection::Intersection(float t, Shape *const obj) {
  this->t = t;
  this->object = obj;
  this->empty = false;
};

bool Intersection::is_empty() { return empty; };

bool operator==(Intersection lhs, Intersection rhs) {
  return (lhs.object == rhs.object && lhs.t == rhs.t);
};

bool operator<(Intersection lhs, Intersection rhs) { return lhs.t < rhs.t; };

Computation Intersection::prepare_computations(Ray r, Intersections xs) {
  Tuple point = r.position(t);
  Tuple eyev = -r.get_direction();
  Tuple normalv = object->normal_at(point);

  Tuple reflectv = r.get_direction().reflect(normalv);

  auto n_vals = compute_n1_and_n2(xs);

  return Computation(t, object, point, eyev, normalv, reflectv, n_vals[0],
                     n_vals[1]);
};

std::vector<float> Intersection::compute_n1_and_n2(Intersections xs) {
  std::vector<Shape *> intersected_objects = std::vector<Shape *>{};
  float n1, n2;
  Intersection curr_intersection;

  for (int i = 0; i < xs.count; i++) {
    curr_intersection = xs[i];
    if (curr_intersection == *this) {
      if (intersected_objects.empty()) {
        n1 = 1.0;
      } else {
        n1 = intersected_objects.back()->get_material().refractive_index;
      };
    };

    auto it = std::find(intersected_objects.begin(), intersected_objects.end(),
                        curr_intersection.object);
    if (it != intersected_objects.end()) {
      intersected_objects.erase(it);
    } else {
      intersected_objects.push_back(curr_intersection.object);
    }

    if (curr_intersection == *this) {
      if (intersected_objects.empty()) {
        n2 = 1.0;
      } else {
        n2 = intersected_objects.back()->get_material().refractive_index;
      };
      break;
    };
  };

  return std::vector<float>{n1, n2};
}

bool Intersection::is_shadowed() { return object->get_throws_shadow(); };
