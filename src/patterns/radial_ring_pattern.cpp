#include "radial_ring_pattern.h"

Color RadialRingPattern::get_a() { return a; };

Color RadialRingPattern::get_b() { return b; };

Color RadialRingPattern::pattern_at(Tuple p) {
  return (int)std::floor(
             std::sqrt(std::pow(p.x, 2) +
                       std::sqrt(std::pow(p.y, 2) + std::pow(p.z, 2)))) %
                     2 ==
                 0
             ? a
             : b;
};
