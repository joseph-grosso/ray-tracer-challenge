#include "cube.hpp"

#include "intersection.hpp"

// TODO: refactor when an intersection is done on a general "object" class
// rather than just the sphere class.
Intersections Cube::local_intersect(Ray r) {
  auto [xtmin, xtmax] = check_axis(r.get_origin().x(), r.get_direction().x());
  auto [ytmin, ytmax] = check_axis(r.get_origin().y(), r.get_direction().y());
  auto [ztmin, ztmax] = check_axis(r.get_origin().z(), r.get_direction().z());

  std::vector<float> max = std::vector<float>{xtmin, ytmin, ztmin};
  std::vector<float> min = std::vector<float>{xtmax, ytmax, ztmax};

  float tmin = *std::max_element(max.begin(), max.end());
  float tmax = *std::min_element(min.begin(), min.end());

  if (tmin > tmax) return Intersections();

  Intersection tmin_inter = Intersection(tmin, this);
  Intersection tmax_inter = Intersection(tmax, this);

  return Intersections(std::vector<Intersection>{tmin_inter, tmax_inter});
};

std::tuple<float, float> Cube::check_axis(float origin, float direction) {
  float tmin_numerator = (-1 - origin);
  float tmax_numerator = (1 - origin);
  float tmin, tmax;

  if (!equalByEpsilon(direction, 0)) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * std::numeric_limits<float>::infinity();
    tmax = tmax_numerator * std::numeric_limits<float>::infinity();
  };

  if (tmin > tmax) {
    float temp = tmin;
    tmin = tmax;
    tmax = temp;
  };

  return std::make_tuple(tmin, tmax);
}

Tuple Cube::local_normal_at(float x, float y, float z) {
  std::vector<float> vals =
      std::vector<float>{std::abs(x), std::abs(y), std::abs(z)};
  float maxc = *std::max_element(vals.begin(), vals.end());

  if (maxc == std::abs(x)) {
    return vector(x, 0, 0);
  } else if (maxc == std::abs(y)) {
    return vector(0, y, 0);
  };
  return vector(0, 0, z);
};
