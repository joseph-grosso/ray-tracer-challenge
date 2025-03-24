#include "smooth_triangle.hpp"

#include "intersection.hpp"

Intersections SmoothTriangle::local_intersect(Ray r) {
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

  Intersection i = Intersection(t, this, u, v);
  return Intersections(std::vector<Intersection>{i});
};

Tuple SmoothTriangle::local_normal_at(float x, float y, float z,
                                      Intersection i) {
  return n2 * i.u + n3 * i.v + n1 * (1 - i.u - i.v);
};

bool operator==(SmoothTriangle lhs, SmoothTriangle rhs) {
  return   
    lhs.p1 == rhs.p1 && 
    lhs.p2 == rhs.p2 && 
    lhs.p3 == rhs.p3 && 
    lhs.n1 == rhs.n1 && 
    lhs.n2 == rhs.n2 && 
    lhs.n3 == rhs.n3 && 
    lhs.e1 == rhs.e1 && 
    lhs.e2 == rhs.e2 &&
    lhs.get_material() == rhs.get_material() &&
    lhs.get_transform() == rhs.get_transform() &&
    lhs.get_throws_shadow() == rhs.get_throws_shadow();
}
