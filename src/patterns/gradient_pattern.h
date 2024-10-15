#pragma once

#include <cmath>

#include "color.h"
#include "matrix.h"
#include "pattern.h"
#include "tuple.h"

class GradientPattern : public Pattern {
 private:
  Color a;
  Color b;

 public:
  GradientPattern(Color a, Color b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  GradientPattern(Color a, Color b)
      : GradientPattern(a, b, identity_matrix(4)){};
  Color get_a() { return a; };
  Color get_b() { return b; };
  Color pattern_at(Tuple p) {
    Color distance = b - a;
    float fraction = p.x - floor(p.x);

    return a + (distance * fraction);
  };
};
