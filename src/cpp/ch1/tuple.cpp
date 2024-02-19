#include "tuple.h"

Tuple::Tuple(float x, float y, float z, float w) {
            this -> x = x;
            this -> y = y;
            this -> z = z;
            this -> w = w;

        }

bool Tuple::isPoint() {
    return w == 1.0;
}

bool Tuple::isVector() {
    return w == 0.0;
}