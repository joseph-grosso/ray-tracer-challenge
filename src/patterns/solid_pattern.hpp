#pragma once

#include "color.h"
#include "matrix.h"
#include "pattern.hpp"
#include "tuple.h"

class SolidPattern : public Pattern {
 private:
  Color color_;

 public:
  SolidPattern(Color color_, Matrix t) : Pattern(t) { this->color_ = color_; };
  SolidPattern(Color color_) : SolidPattern(color_, identity_matrix(4)){};
  Color get_color() { return color_; };
  Color pattern_at(Tuple p) {
    return get_color();
  };  // must be a point, not vector
};
