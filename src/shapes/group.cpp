#include "group.hpp"

Tuple Group::local_normal_at(float x, float y, float z) {
  return point(0, 0, 0);
};

Tuple Group::local_normal_at(Tuple p, Intersection i) {
  return point(0, 0, 0);
};

std::string Group::to_string() { return "Group()"; };

Intersections Group::local_intersect(Ray r) {
  if (is_empty()) {
    return Intersections();
  };

  std::vector<Intersection> xs = std::vector<Intersection>{};
  std::vector<Intersection> intersections;

  for (int i = 0; i < get_count(); i++) {
    intersections = children[i]->intersect(r).data;
    xs.insert(xs.end(), intersections.begin(), intersections.end());
  };

  // TODO: optimize by removing sorting from this step as it isn't required.
  // That work is already done in the World step.
  // Add/fix tests when this is done.
  std::sort(xs.begin(), xs.end());
  return Intersections(xs);
};

void Group::set_all_materials(Material m) {
  // TODO: for nested groups you'll need a better setter method call
  for (auto child : children) {
    child->set_material(m);
  };
};
