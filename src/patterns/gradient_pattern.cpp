#include "gradient_pattern.h"


Color GradientPattern::get_a() {
    return a;
};

Color GradientPattern::get_b() {
    return b;
};

Color GradientPattern::pattern_at(Tuple p) {
    Color distance = b - a;
    float fraction = p.x - floor(p.x);

    return a + (distance * fraction);
};
