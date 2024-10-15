#pragma once

#include <cmath>

#include "PerlinNoise.hpp"
#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class PerlinPattern : public Pattern {
 private:
  Pattern *a;
  Pattern *b;
  siv::PerlinNoise perlin;

 public:
  PerlinPattern(Pattern *a, Pattern *b, long unsigned int seed, Matrix t)
      : Pattern(t) {
    this->a = a;
    this->b = b;
    this->perlin = siv::PerlinNoise{seed};
  };
  PerlinPattern(Pattern *a, Pattern *b, long unsigned int seed)
      : PerlinPattern(a, b, seed, identity_matrix(4)){};
  Pattern *get_a() { return a; };
  Pattern *get_b() { return b; };
  Color pattern_at(Tuple p) {
    Color a_col = a->pattern_at(a->get_transform().inverse() * p);
    Color b_col = b->pattern_at(b->get_transform().inverse() * p);

    return perlin.noise3D_01(p.x, p.y, p.z) > 0.5 ? a_col : b_col;
  };
};
