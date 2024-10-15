#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class GradientPattern : public Pattern {
 private:
  Pattern* a;
  Pattern* b;

 public:
  GradientPattern(Pattern* a, Pattern* b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  GradientPattern(Pattern* a, Pattern* b)
      : GradientPattern(a, b, identity_matrix(4)){};
  Pattern* get_a() { return a; };
  Pattern* get_b() { return b; };
  Color pattern_at(Tuple p) {
    Color a_col = a->pattern_at(a->get_transform().inverse() * p);
    Color b_col = b->pattern_at(b->get_transform().inverse() * p);

    Color distance = b_col - a_col;
    float fraction = p.x - floor(p.x);

    return a_col + (distance * fraction);
  };
};
