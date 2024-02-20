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

bool operator==(Tuple lhs, Tuple rhs) { 
    return equalByEpsilon(lhs.x, rhs.x)
        && equalByEpsilon(lhs.y, rhs.y)
        && equalByEpsilon(lhs.z, rhs.z)
        && equalByEpsilon(lhs.w, rhs.w);
}

Tuple operator+(Tuple lhs, Tuple rhs) { 
    return Tuple(
        lhs.x  + rhs.x,
        lhs.y  + rhs.y,
        lhs.z  + rhs.z,
        lhs.w  + rhs.w
    );
}

Tuple operator-(Tuple lhs, Tuple rhs) {
    return Tuple(
        lhs.x  - rhs.x,
        lhs.y  - rhs.y,
        lhs.z  - rhs.z,
        lhs.w  - rhs.w
    );
}

Tuple operator-(Tuple tup) {
    return Tuple(
        -tup.x,
        -tup.y,
        -tup.z,
        -tup.w
    );
}

Tuple operator*(Tuple tup, float a) {
    return Tuple(
        tup.x * a,
        tup.y * a,
        tup.z * a,
        tup.w * a
    );
};

Tuple operator*(float a, Tuple tup) {
    return Tuple(
        tup.x * a,
        tup.y * a,
        tup.z * a,
        tup.w * a
    );
};

Tuple operator/(Tuple tup, float a) {
    return Tuple(
        tup.x / a,
        tup.y / a,
        tup.z / a,
        tup.w / a
    );
};
