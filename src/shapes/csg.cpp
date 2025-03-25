#include "csg.hpp"

Tuple CSG::local_normal_at(float x, float y, float z) {
  return vector(x, y, z);
};

Tuple CSG::local_normal_at(Tuple p, Intersection i) {
  return local_normal_at(p.x, p.y, p.z);
};

std::string CSG::to_string() { return "CSG"; };

Intersections CSG::local_intersect(Ray r) {
  return Intersections(std::vector<Intersection>{});
};

bool CSG::intersection_allowed(bool lhit, bool inl, bool inr) {
  if (operation == CSGOperation::UNION) {
    return (lhit && !inr) || (!lhit && !inl);
  } else if (operation == CSGOperation::INTERSECTION) {
    return (lhit && inr) || (!lhit && inl);
  } else if (operation == CSGOperation::DIFFERENCE) {
    return (lhit && !inr) || (!lhit && inl);
  };
  return false;
};
