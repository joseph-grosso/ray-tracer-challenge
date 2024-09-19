#pragma once

#include "tuple.h"

#include <cmath>

class StripePattern {
    private:
        Color a;
        Color b;
    public:
        StripePattern(Color a, Color b);
        Color get_a();
        Color get_b();
        Color stripe_at(Tuple p);  // must be a point, not vector
};
