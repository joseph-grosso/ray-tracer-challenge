#include "stripe_pattern.h"
#include <cmath>

StripePattern::StripePattern(Color a, Color b) {
    this->a = a;
    this->b = b;
};

Color StripePattern::get_a() {
    return a;
};

Color StripePattern::get_b() {
    return b;
};

Color StripePattern::stripe_at(Tuple p) {
    return ((int) std::floor(p.x) % 2 == 0) ? a : b;
};