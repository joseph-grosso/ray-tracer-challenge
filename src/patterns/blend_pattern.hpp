#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class BlendPattern : public Pattern {
 private:
  Pattern *a;
  Pattern *b;
  float blend_percent;

 public:
  BlendPattern(Pattern *a, Pattern *b, float blend_percent, Matrix t)
      : Pattern(t) {
    this->a = a;
    this->b = b;
    this->blend_percent = blend_percent;
  };
  BlendPattern(Pattern *a, Pattern *b, Matrix t) : BlendPattern(a, b, 0.5, t){};
  BlendPattern(Pattern *a, Pattern *b, float blend_percent)
      : BlendPattern(a, b, blend_percent, identity_matrix(4)){};
  BlendPattern(Pattern *a, Pattern *b)
      : BlendPattern(a, b, 0.5, identity_matrix(4)){};
  Pattern *get_a() { return a; };
  Pattern *get_b() { return b; };
  Color pattern_at(Tuple p) {
    Color a_col = a->pattern_at(a->get_transform_inverse() * p);
    Color b_col = b->pattern_at(b->get_transform_inverse() * p);

    return a_col * blend_percent + b_col * (1 - blend_percent);
  };
};
