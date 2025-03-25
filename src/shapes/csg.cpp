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

Intersections CSG::filter_intersections(Intersections xs) {
  bool inl = false;
  bool inr = false;
  bool lhit;

  auto result = std::vector<Intersection>{};

  for (auto i : xs.data) {
    lhit = left->includes(i.object);  // virtual method for getting values
    if (intersection_allowed(lhit, inl, inr)) {
      result.push_back(i);
    };

    if (lhit) {
      inl = !inl;
    } else {
      inr = !inr;
    };
  };
  return Intersections(result);
};
