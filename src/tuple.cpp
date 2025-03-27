#include "tuple.hpp"

// Chapter 1: Tuples, Vectors and Points
// Functions to create new tuples
Tuple point(float x, float y, float z) { return Tuple(x, y, z, 1.0); }

Tuple vector(float x, float y, float z) { return Tuple(x, y, z, 0); }

bool equalByEpsilon(float a, float b, float epsilon) {
  // return a <= b + epsilon && a >= b - epsilon;
  return std::abs(a - b) <= epsilon;
}

bool operator==(Tuple lhs, Tuple rhs) {
  return equalByEpsilon(lhs.x(), rhs.x()) && equalByEpsilon(lhs.y(), rhs.y()) &&
         equalByEpsilon(lhs.z(), rhs.z()) && equalByEpsilon(lhs.w(), rhs.w());
}

Tuple operator+(Tuple lhs, Tuple rhs) {
  return Tuple(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(),
               lhs.w() + rhs.w());
}

Tuple operator-(Tuple lhs, Tuple rhs) {
  return Tuple(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(),
               lhs.w() - rhs.w());
}

Tuple operator-(Tuple tup) {
  return Tuple(-tup.x(), -tup.y(), -tup.z(), -tup.w());
}

Tuple operator*(Tuple tup, float a) {
  return Tuple(tup.x() * a, tup.y() * a, tup.z() * a, tup.w() * a);
};

Tuple operator*(float a, Tuple tup) {
  return Tuple(tup.x() * a, tup.y() * a, tup.z() * a, tup.w() * a);
};

Tuple operator/(Tuple tup, float a) {
  return Tuple(tup.x() / a, tup.y() / a, tup.z() / a, tup.w() / a);
};

// Chapter 7: Making a Scene
// Defining a view transform
void PrintTo(const Tuple &m, std::ostream *os) {
  Tuple &ref = const_cast<Tuple &>(m);
  *os << ref.to_string();
}
