#pragma once

#include "tuple.h"
#include "matrix.h"
#include "color.h"
#include "pattern.h"

#include <cmath>


class CheckersPattern : public Pattern {
    private:
        Color a;
        Color b;
    public:
        CheckersPattern(Color a, Color b, Matrix t) : Pattern(t) {
            this->a = a;
            this->b = b;
        };
        CheckersPattern(Color a, Color b) : CheckersPattern(a, b, identity_matrix(4)) {};
        Color get_a();
        Color get_b();
        Color pattern_at(Tuple p);
};
