#pragma once

#include <cmath>

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class CheckersPattern : public Pattern {
 private:
  Pattern *a;
  Pattern *b;

 public:
  CheckersPattern(Pattern *a, Pattern *b, Matrix t) : Pattern(t) {
    this->a = a;
    this->b = b;
  };
  CheckersPattern(Pattern *a, Pattern *b)
      : CheckersPattern(a, b, identity_matrix(4)){};
  Pattern *get_a() { return a; };
  Pattern *get_b() { return b; };
  Color pattern_at(Tuple p) {
    int abs_distances = (int)std::abs(std::floor(p.x())) +
                        std::abs(std::floor(p.y())) +
                        std::abs(std::floor(p.z()));
    return abs_distances % 2 == 0
               ? a->pattern_at(a->get_transform_inverse() * p)
               : b->pattern_at(b->get_transform_inverse() * p);
  };
};
