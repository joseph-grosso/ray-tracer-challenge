#include "cylinder.hpp"

#include "intersection.hpp"

Intersections Cylinder::local_intersect(Ray r) {
  float a = std::pow(r.get_direction().x, 2) + std::pow(r.get_direction().z, 2);

  // check if ray is parallel to the y axis
  if (equalByEpsilon(a, 0)) {
    return Intersections();
  };

  float b = 2 * r.get_origin().x * r.get_direction().x +
            2 * r.get_origin().z * r.get_direction().z;
  float c = std::pow(r.get_origin().x, 2) + std::pow(r.get_origin().z, 2) - 1;
  float disc = std::pow(b, 2) - 4 * a * c;

  // ray doesn't intersect cylinder
  if (disc < 0) {
    return Intersections();
  };

  Intersection t0 = Intersection((-b - std::sqrt(disc)) / (2 * a), this);
  Intersection t1 = Intersection((-b + std::sqrt(disc)) / (2 * a), this);
  return Intersections(std::vector<Intersection>{t0, t1});
};

Tuple Cylinder::local_normal_at(float x, float y, float z) {
  return vector(0, 0, 0);
};
