#pragma once

#include "tuple.h"
#include "matrix.h"
#include "color.h"
#include "pattern.h"

#include <cmath>

class ConicalRingPattern : public Pattern {
    private:
        Color a;
        Color b;
    public:
        ConicalRingPattern(Color a, Color b, Matrix t) : Pattern(t) {
            this->a = a;
            this->b = b;
        };
        ConicalRingPattern(Color a, Color b) : ConicalRingPattern(a, b, identity_matrix(4)) {};
        Color get_a();
        Color get_b();
        Color pattern_at(Tuple p);
};
