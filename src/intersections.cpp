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
