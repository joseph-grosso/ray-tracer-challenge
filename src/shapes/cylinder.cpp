#include "cylinder.hpp"

#include "intersection.hpp"

Intersections Cylinder::local_intersect(Ray r) {
  std::vector<Intersection> xs = std::vector<Intersection>{};

  float a =
      std::pow(r.get_direction().x(), 2) + std::pow(r.get_direction().z(), 2);

  // check if ray is parallel to the y axis
  if (equalByEpsilon(a, 0)) {
    intersect_caps(r, &xs);
    return xs;
  };

  float b = 2 * r.get_origin().x() * r.get_direction().x() +
            2 * r.get_origin().z() * r.get_direction().z();
  float c =
      std::pow(r.get_origin().x(), 2) + std::pow(r.get_origin().z(), 2) - 1;
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

  float y0 = r.get_origin().y() + t0 * r.get_direction().y();
  if (minimum < y0 && y0 < maximum) {
    xs.push_back(Intersection(t0, this));
  };

  float y1 = r.get_origin().y() + t1 * r.get_direction().y();
  if (minimum < y1 && y1 < maximum) {
    xs.push_back(Intersection(t1, this));
  };

  intersect_caps(r, &xs);

  return Intersections(xs);
};

Tuple Cylinder::local_normal_at(float x, float y, float z) {
  // square of distance from the y axis
  float dist = std::pow(x, 2) + std::pow(z, 2);

  if (dist < 1 && y >= maximum - 0.0001) {  // TODO: replace with the epsilon
    return vector(0, 1, 0);
  } else if (dist < 1 &&
             y <= minimum + 0.0001) {  // TODO: replace with the epsilon
    return vector(0, -1, 0);
  };

  return vector(x, 0, z);
};

bool Cylinder::check_cap(Ray r, float t) {
  float x = r.get_origin().x() + t * r.get_direction().x();
  float z = r.get_origin().z() + t * r.get_direction().z();

  float val = std::pow(x, 2) + std::pow(z, 2);

  return val <= 1.0 || equalByEpsilon(val, 1.0);
};

void Cylinder::intersect_caps(Ray ray, std::vector<Intersection> *xs) {
  if (!this->closed || equalByEpsilon(ray.get_direction().y(), 0)) {
    return;
  };

  float t = (minimum - ray.get_origin().y()) / ray.get_direction().y();
  if (check_cap(ray, t)) {
    xs->push_back(Intersection(t, this));
  };

  t = (maximum - ray.get_origin().y()) / ray.get_direction().y();
  if (check_cap(ray, t)) {
    xs->push_back(Intersection(t, this));
  };
};
