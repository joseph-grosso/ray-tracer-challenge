#pragma once

#include "tuple.h"
#include "matrix.h"

#include <cmath>

class Shape;

class StripePattern {
    private:
        Color a;
        Color b;
        Matrix transform;
    public:
        StripePattern(Color a, Color b);
        Color get_a();
        Color get_b();
        void set_transform(Matrix t);
        Color stripe_at(Tuple p);  // must be a point, not vector
        Color stripe_at_object(Shape * object, Tuple point_);
};
