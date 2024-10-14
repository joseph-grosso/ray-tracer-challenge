#pragma once

#include "color.h"
#include "matrix.h"
#include "pattern.h"
#include "tuple.h"

#include <cmath>

class StripePattern : public Pattern {
private:
  Color a;
  Color b;

public:
  StripePattern(Color a, Color b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  StripePattern(Color a, Color b) : StripePattern(a, b, identity_matrix(4)){};
  Color get_a();
  Color get_b();
  Color pattern_at(Tuple p); // must be a point, not vector
};
