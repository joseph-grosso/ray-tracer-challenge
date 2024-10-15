#pragma once

#include <cmath>

#include "color.h"
#include "matrix.h"
#include "pattern.hpp"
#include "tuple.h"

class CheckersPattern : public Pattern {
 private:
  Color a;
  Color b;

 public:
  CheckersPattern(Color a, Color b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  CheckersPattern(Color a, Color b)
      : CheckersPattern(a, b, identity_matrix(4)){};
  Color get_a() { return a; };
  Color get_b() { return b; };
  Color pattern_at(Tuple p) {
    int abs_distances = (int)(std::abs(p.x) + std::abs(p.y) + std::abs(p.z));
    return abs_distances % 2 == 0 ? a : b;
  };
};
