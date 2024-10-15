#pragma once

#include <cmath>

#include "color.hpp"
#include "lights.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class Shape;

class Material {
 public:
  Material(Pattern *pattern = NULL, Color color = Color(1, 1, 1),
           float ambient = 0.1, float diffuse = 0.9, float specular = 0.9,
           float shininess = 200.0);
  Material(Color color, float ambient, float diffuse, float specular,
           float shininess)
      : Material(NULL, color, ambient, diffuse, specular, shininess){};
  Pattern *pattern;
  Color color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
  std::string to_string();
  Color lighting(Shape *object, PointLight light, Tuple position, Tuple eyev,
                 Tuple normalv, bool in_shadow);
};

bool operator==(Material lhs, Material rhs);