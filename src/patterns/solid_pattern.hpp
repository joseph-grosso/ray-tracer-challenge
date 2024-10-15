#pragma once

#include "color.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class SolidPattern : public Pattern {
 private:
  Color color_;

 public:
  SolidPattern(Color color_, Matrix t) : Pattern(t) { this->color_ = color_; };
  SolidPattern(Color color_) : SolidPattern(color_, identity_matrix(4)){};
  SolidPattern(float r, float g, float b) : SolidPattern(Color(r, g, b)){};
  Color get_color() { return color_; };
  Color pattern_at(Tuple p) {
    return get_color();
  };  // must be a point, not vector
};
