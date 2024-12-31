#pragma once

#include <cmath>

#include "PerlinNoise.hpp"
#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class PermutationPattern : public Pattern {
 private:
  Pattern *base_pattern;
  float noise_scaling;
  siv::PerlinNoise perlin_x;
  siv::PerlinNoise perlin_y;
  siv::PerlinNoise perlin_z;

 public:
  PermutationPattern(Pattern *base_pattern, float noise_scaling = 1.0,
                     long unsigned int seed = 0)
      : Pattern(base_pattern->get_transform()) {
    this->base_pattern = base_pattern;
    this->perlin_x = siv::PerlinNoise{seed};
    this->perlin_y = siv::PerlinNoise{seed + 1};
    this->perlin_z = siv::PerlinNoise{seed + 2};
    this->noise_scaling = noise_scaling;
  };
  Pattern *get_base_pattern() { return base_pattern; };
  Color pattern_at(Tuple p) {
    double pval_x = perlin_x.octave3D_11(p.x, p.y, p.z, 3) * noise_scaling;
    double pval_y = perlin_y.octave3D_11(p.x, p.y, p.z, 3) * noise_scaling;
    double pval_z = perlin_z.octave3D_11(p.x, p.y, p.z, 3) * noise_scaling;

    return base_pattern->pattern_at(p + vector(pval_x, pval_y, pval_z));
  };
};
