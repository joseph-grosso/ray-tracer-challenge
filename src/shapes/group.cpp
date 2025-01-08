#include "group.hpp"

Tuple Group::local_normal_at(float x, float y, float z) {
  return point(0, 0, 0);
};

Tuple Group::local_normal_at(Tuple p) { return point(0, 0, 0); };

std::string Group::to_string() { return "Group()"; };

Intersections Group::local_intersect(Ray r) { return Intersections(); };
