#pragma once

#include "color.h"
#include "matrix.h"
#include "pattern.h"
#include "tuple.h"

#include <cmath>

class RadialRingPattern : public Pattern {
private:
  Color a;
  Color b;

public:
  RadialRingPattern(Color a, Color b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  RadialRingPattern(Color a, Color b)
      : RadialRingPattern(a, b, identity_matrix(4)){};
  Color get_a();
  Color get_b();
  Color pattern_at(Tuple p);
};
