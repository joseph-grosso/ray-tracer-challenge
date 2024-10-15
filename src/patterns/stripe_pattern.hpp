#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

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
  Color get_a() { return a; };
  Color get_b() { return b; };
  Color pattern_at(Tuple p) { return ((int)std::floor(p.x) % 2 == 0) ? a : b; };
};
