#include "tuple.h"
#include <cmath>


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

// Functions to create tuples
Tuple point(float x, float y, float z) {
    return Tuple(x, y, z, 1.0);
}

Tuple vector(float x, float y, float z) {
    return Tuple(x, y, z, 0);
}

bool equalByEpsilon(float a, float b, float epsilon) {
    // return a <= b + epsilon && a >= b - epsilon;
    return std::abs(a - b) <= epsilon;
}

bool Tuple::operator==(Tuple & rhs) { 
    return equalByEpsilon(this->x, rhs.x)
        && equalByEpsilon(this->y, rhs.y)
        && equalByEpsilon(this->z, rhs.z)
        && equalByEpsilon(this->w, rhs.w);
}

Tuple Tuple::operator+(Tuple & rhs) { 
    return Tuple(
        this->x  + rhs.x,
        this->y  + rhs.y,
        this->z  + rhs.z,
        this->w  + rhs.w
    );
}

Tuple Tuple::operator-(Tuple & rhs) {
    return Tuple(
        this->x  - rhs.x,
        this->y  - rhs.y,
        this->z  - rhs.z,
        this->w  - rhs.w
    );
}

Tuple Tuple::operator-() {
    return Tuple(
        -this->x,
        -this->y,
        -this->z,
        -this->w
    );
}