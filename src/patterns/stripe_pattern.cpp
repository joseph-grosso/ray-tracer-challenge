#include "stripe_pattern.h"
#include "shape.h"

StripePattern::StripePattern(Color a, Color b, Matrix t) {
    this->a = a;
    this->b = b;
    this->transform = t;
};

Color StripePattern::get_a() {
    return a;
};

Color StripePattern::get_b() {
    return b;
};

Color StripePattern::stripe_at(Tuple p) {
    return ((int) std::floor(p.x) % 2 == 0) ? a : b;
};

void StripePattern::set_transform(Matrix t) {
    this->transform = t;
};

Color StripePattern::stripe_at_object(Shape * object, Tuple point_) {
    Tuple obj_point = (*object).get_transform().inverse() * point_;
    Tuple pattern_point = this->transform.inverse() * obj_point;

    return stripe_at(pattern_point);
}
