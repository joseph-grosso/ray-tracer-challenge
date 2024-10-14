#include "conical_ring_pattern.h"


Color ConicalRingPattern::get_a() {
    return a;
};

Color ConicalRingPattern::get_b() {
    return b;
};

Color ConicalRingPattern::pattern_at(Tuple p) {
    return (int) std::floor(std::sqrt(std::pow(p.x, 2) + std::pow(p.z, 2))) % 2 == 0 ? a : b;
};
