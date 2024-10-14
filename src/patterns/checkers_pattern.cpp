#include "checkers_pattern.h"


Color CheckersPattern::get_a() {
    return a;
};

Color CheckersPattern::get_b() {
    return b;
};

Color CheckersPattern::pattern_at(Tuple p) {
    return (int) (std::abs(p.x) + std::abs(p.y) + std::abs(p.z)) % 2 == 0 ? a : b;
};
