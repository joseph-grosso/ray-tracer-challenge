#pragma once

#include <bits/stdc++.h>

#include <iostream>
#include <vector>

#include "color.hpp"
#include "computation.hpp"
#include "intersection.hpp"
#include "intersections.hpp"
#include "lights.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "transform.hpp"
#include "tuple.hpp"

class World {
 private:
  float calculate_angle_ratio(Computation comps) {
    float n_ratio = comps.n1 / comps.n2;
    float cos_i = comps.eyev.dot(comps.normalv);
    return n_ratio * n_ratio * (1 - cos_i * cos_i);
  };

 public:
  std::vector<Shape *> objects;
  std::vector<PointLight> lights;
  World(std::vector<Shape *> objects = std::vector<Shape *>{},
        std::vector<PointLight> lights = std::vector<PointLight>{});
  World(Shape *s, PointLight l)
      : World(std::vector<Shape *>(1, s), std::vector<PointLight>{1, l}){};
  World(std::vector<Shape *> s_list, PointLight l)
      : World(s_list, std::vector<PointLight>{1, l}){};
  Intersections intersect_world(Ray r);
  Color shade_hit(Computation comp, int remaining = 5);
  Color color_at(Ray r, int remaining = 5);
  Color reflected_color(Computation comp, int remaining = 5);
  bool is_shadowed(Tuple p);
  Color refracted_color(Computation comps, int remaining);
};

World default_world();
