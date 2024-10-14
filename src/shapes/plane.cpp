#include "plane.h"
#include "intersection.h"

// Chapter 9: Planes
Tuple Plane::local_normal_at(float x, float y, float z) {
  return local_normal_at(point(x, y, z));
};

Tuple Plane::local_normal_at(Tuple p) { return normal; };

// TODO: refactor when an intersection is done on a general "object" class
// rather than just the sphere class.
Intersections Plane::local_intersect(Ray r) {
  if (std::abs(r.get_direction().y) < 0.0001) {
    return Intersections(); // no intersections
  };
  float t = -(r.get_origin().y) / r.get_direction().y;
  Intersection i = Intersection(t, this);
  return Intersections(std::vector<Intersection>{i});
};