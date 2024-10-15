#pragma once

#include <cmath>

#include "color.h"
#include "matrix.h"
#include "pattern.hpp"
#include "tuple.h"

class ConicalRingPattern : public Pattern {
 private:
  Color a;
  Color b;

 public:
  ConicalRingPattern(Color a, Color b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  ConicalRingPattern(Color a, Color b)
      : ConicalRingPattern(a, b, identity_matrix(4)){};
  Color get_a() { return a; };
  Color get_b() { return b; };
  Color pattern_at(Tuple p) {
    return (int)std::floor(std::sqrt(std::pow(p.x, 2) + std::pow(p.z, 2))) %
                       2 ==
                   0
               ? a
               : b;
  };
};
