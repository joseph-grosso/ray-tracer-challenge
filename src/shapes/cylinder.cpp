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

  float t0 = (-b - std::sqrt(disc)) / (2 * a);
  float t1 = (-b + std::sqrt(disc)) / (2 * a);
  if (t0 > t1) {
    float temp = t1;
    t1 = t0;
    t0 = temp;
  };

  std::vector<Intersection> xs = std::vector<Intersection>{};

  float y0 = r.get_origin().y + t0 * r.get_direction().y;
  if (minimum < y0 && y0 < maximum) {
    xs.push_back(Intersection(t0, this));
  };

  float y1 = r.get_origin().y + t1 * r.get_direction().y;
  if (minimum < y1 && y1 < maximum) {
    xs.push_back(Intersection(t1, this));
  };

  return Intersections(xs);
};

Tuple Cylinder::local_normal_at(float x, float y, float z) {
  return vector(x, 0, z);
};
