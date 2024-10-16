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
  Color shade_hit(Computation comp);
  Color color_at(Ray r);
  bool is_shadowed(Tuple p);
};

World default_world();