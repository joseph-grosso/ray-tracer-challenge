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
  bool fade_together;

 public:
  PerlinPattern(Pattern *a, Pattern *b, long unsigned int seed,
                Matrix t = identity_matrix(4), bool fade_together = false)
      : Pattern(t) {
    this->a = a;
    this->b = b;
    this->perlin = siv::PerlinNoise{seed};
    this->fade_together = fade_together;
  };
  Pattern *get_a() { return a; };
  Pattern *get_b() { return b; };
  Color pattern_at(Tuple p) {
    Color a_color = a->pattern_at(a->get_transform().inverse() * p);
    Color b_color = b->pattern_at(b->get_transform().inverse() * p);
    double perlin_value = perlin.noise3D_01(p.x(), p.y(), p.z());

    if (fade_together) {
      return (perlin_value * a_color) +
             ((1 - perlin.noise3D_01(p.x(), p.y(), p.z())) * b_color);
    };
    return perlin.noise3D_01(p.x(), p.y(), p.z()) > 0.5 ? a_color : b_color;
  };
};
