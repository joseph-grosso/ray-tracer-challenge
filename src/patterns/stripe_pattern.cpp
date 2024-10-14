#include "stripe_pattern.h"
#include "shape.h"


Color StripePattern::get_a() {
    return a;
};

Color StripePattern::get_b() {
    return b;
};

Color StripePattern::pattern_at(Tuple p) {
    return ((int) std::floor(p.x) % 2 == 0) ? a : b;
};
