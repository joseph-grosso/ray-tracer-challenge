#pragma once

#include "tuple.h"
#include "matrix.h"
#include "color.h"
#include "pattern.h"

#include <cmath>

class Shape;

class StripePattern : public Pattern {
    private:
        Color a;
        Color b;
    public:
        StripePattern(Color a, Color b, Matrix t) : Pattern(t) {
            this->a = a;
            this->b = b;
        };
        StripePattern(Color a, Color b) : StripePattern(a, b, identity_matrix(4)) {};
        Color get_a();
        Color get_b();
        Color pattern_at(Tuple p);  // must be a point, not vector
};
