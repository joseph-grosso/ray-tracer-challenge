#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class ConicalRingPattern : public Pattern {
 private:
  Pattern* a;
  Pattern* b;

 public:
  ConicalRingPattern(Pattern* a, Pattern* b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  ConicalRingPattern(Pattern* a, Pattern* b)
      : ConicalRingPattern(a, b, identity_matrix(4)){};
  Pattern* get_a() { return a; };
  Pattern* get_b() { return b; };
  Color pattern_at(Tuple p) {
    int orig_distance =
        (int)std::floor(std::sqrt(std::pow(p.x(), 2) + std::pow(p.z(), 2)));
    return orig_distance % 2 == 0
               ? a->pattern_at(a->get_transform_inverse() * p)
               : b->pattern_at(b->get_transform_inverse() * p);
  };
};
