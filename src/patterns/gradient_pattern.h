#pragma once

#include "tuple.h"
#include "matrix.h"
#include "color.h"
#include "pattern.h"

#include <cmath>

class GradientPattern : public Pattern {
    private:
        Color a;
        Color b;
    public:
        GradientPattern(Color a, Color b, Matrix t) : Pattern(t) {
            this->a = a;
            this->b = b;
        };
        GradientPattern(Color a, Color b) : GradientPattern(a, b, identity_matrix(4)) {};
        Color get_a();
        Color get_b();
        Color pattern_at(Tuple p);
};
