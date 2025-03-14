#include "triangle.hpp"

#include <iostream>

#include "intersection.hpp"

Intersections Triangle::local_intersect(Ray r) {
  // Moller-Trumbore algorithm
  Tuple dir_cross_e2 = r.get_direction().cross(e2);
  float det = e1.dot(dir_cross_e2);

  if (equalByEpsilon(det, 0)) {
    return Intersections();
  };

  float f = 1.0 / det;
  Tuple p1_to_origin = r.get_origin() - p1;
  float u = f * p1_to_origin.dot(dir_cross_e2);
  if (u < 0 || u > 1) {
    return Intersections();
  };

  Tuple origin_cross_e1 = p1_to_origin.cross(e1);
  float v = f * r.get_direction().dot(origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return Intersections();
  };

  float t = f * e2.dot(origin_cross_e1);

  Intersection i = Intersection(t, this);
  return Intersections(std::vector<Intersection>{i});
};

Tuple Triangle::local_normal_at(float x, float y, float z) { return normal; };
