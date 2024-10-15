#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

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
  Color get_a() { return a; };
  Color get_b() { return b; };
  Color pattern_at(Tuple p) {
    return (int)std::floor(
               std::sqrt(std::pow(p.x, 2) +
                         std::sqrt(std::pow(p.y, 2) + std::pow(p.z, 2)))) %
                       2 ==
                   0
               ? a
               : b;
  };
};
