#include "computation.hpp"

// Chapter 7: Building a World
Computation::Computation(float t, Shape *object, Tuple point, Tuple eyev,
                         Tuple normalv, Tuple reflectv, float n1, float n2) {
  this->t = t;
  this->object = object;
  this->point = point;
  this->eyev = eyev;
  this->reflectv = reflectv;
  if (normalv.dot(eyev) < 0) {
    this->inside = true;
    this->normalv = -normalv;
  } else {
    this->inside = false;
    this->normalv = normalv;
  };
  // TODO: Create epsilon constant that is shared around the codebase
  // TODO: Fix the shading function to
  // * make epsilon here smaller
  // * Reduce acne when epsilon is smaller
  this->over_point = this->point + this->normalv * 0.002;   // EPSILON
  this->under_point = this->point - this->normalv * 0.002;  // EPSILON
  this->n1 = n1;
  this->n2 = n2;
};

float Computation::schlick() {
  // find the cosine of the nalge b/w the eye and normal vectors
  float cos = eyev.dot(normalv);

  // total internal reflection can only occur if n1 > n2
  if (n1 > n2) {
    float n = n1 / n2;
    float sin2_t = n * n * (1.0F - cos * cos);
    if (sin2_t > 1.0F) {
      return 1.0;
    };
  }
  return 0;
};

std::string Computation::to_string() {
  return "Computation(Vector Distance=" + std::to_string(t) +
         ", Object Transform=" +  // Not implemented yet
         ", point=" + point.to_string() +
         ", over_point=" + over_point.to_string() +
         ", under_point=" + under_point.to_string() +
         ", eyev=" + eyev.to_string() + ", normalv=" + normalv.to_string() +
         ", reflectv=" + reflectv.to_string() +
         ", inside=" + std::to_string(inside) + ", n1=" + std::to_string(n1) +
         ", n2=" + std::to_string(n2) + ")";
}