#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class RadialRingPattern : public Pattern {
 private:
  Pattern* a;
  Pattern* b;

 public:
  RadialRingPattern(Pattern* a, Pattern* b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  RadialRingPattern(Pattern* a, Pattern* b)
      : RadialRingPattern(a, b, identity_matrix(4)){};
  Pattern* get_a() { return a; };
  Pattern* get_b() { return b; };
  Color pattern_at(Tuple p) {
    int origin_distance = (int)std::floor(
        std::sqrt(std::pow(p.x(), 2) +
                  std::sqrt(std::pow(p.y(), 2) + std::pow(p.z(), 2))));
    return origin_distance % 2 == 0
               ? a->pattern_at(a->get_transform().inverse() * p)
               : b->pattern_at(b->get_transform().inverse() * p);
  };
};
