#include "intersections.hpp"

#include <stdexcept>
#include <vector>

#include "intersection.hpp"
#include "ray.hpp"

Intersections::Intersections(std::vector<Intersection> data) {
  this->data = data;
  this->count = data.size();
};

Intersection Intersections::operator[](int i) { return data[i]; };

Intersection Intersections::hit() {
  if (count == 0) {
    // TODO: Think about other ways you could avoid throwing this if this causes
    // issues in the future. return null intersection? return Intersection();
    return Intersection();
  };

  Intersection inter = data[0];

  for (int i = 0; i < count; i++) {
    if (data[i].t == 0) {
      return data[i];
    }
    if ((inter.t < 0) || (data[i].t >= 0 && data[i].t < inter.t)) {
      inter = data[i];
    };
  };

  // return the chosen value if valid, if not return empty intersection.
  return (inter.t >= 0) ? inter : Intersection();
};

// 4 conditions:
// * the intersection is not empty
// * the intersection occurs after the origin of the ray
// * the intersection occurs before getting to the light source
// * the object intersected comes before the ray hits the light source
bool Intersections::is_shadowed(float light_distance) {
  if (count == 0) {
    return false;
  };

  for (int i = 0; i < count; i++) {
    if (data[i].is_empty() || data[i].t < 0) {
      continue;
    } else if (data[i].t > light_distance) {
      break;
    } else if (data[i].is_shadowed()) {
      return true;
    };
  };
  return false;
};
