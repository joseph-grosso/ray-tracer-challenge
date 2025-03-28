#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class StripePattern : public Pattern {
 private:
  Pattern* a;
  Pattern* b;

 public:
  StripePattern(Pattern* a, Pattern* b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  StripePattern(Pattern* a, Pattern* b)
      : StripePattern(a, b, identity_matrix(4)){};
  Pattern* get_a() { return a; };
  Pattern* get_b() { return b; };
  Color pattern_at(Tuple p) {
    return ((int)std::floor(p.x()) % 2 == 0)
               ? a->pattern_at(a->get_transform_inverse() * p)
               : b->pattern_at(b->get_transform_inverse() * p);
  };
};
