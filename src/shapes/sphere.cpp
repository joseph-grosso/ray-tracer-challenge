#include "sphere.hpp"

Tuple Sphere::get_center() { return center; };

float Sphere::get_radius() { return radius; };

bool operator==(Sphere lhs, Sphere rhs) {
  return (lhs.get_center() == rhs.get_center() &&
          equalByEpsilon(lhs.get_radius(), rhs.get_radius()) &&
          lhs.get_transform() == rhs.get_transform() &&
          lhs.get_material() == rhs.get_material());
};

bool operator!=(Sphere lhs, Sphere rhs) { return !(lhs == rhs); };

// chapter 6: Lighting and Shading
Tuple Sphere::local_normal_at(float x, float y, float z) {
  // Algorithm explanation: p80 - p82
  return local_normal_at(point(x, y, z));
};

Tuple Sphere::local_normal_at(Tuple p) {
  // Algorithm explanation: p80 - p82
  return p - point(0, 0, 0);
};

std::string Sphere::to_string() {
  return "\nTransform:\n" + transformation.to_string() +
         "\nMaterial: " + material.to_string();
};

Intersections Sphere::local_intersect(Ray r) {
  // the vector from the sphere's center to the ray origin
  // Remember: the sphere is centered at the world origin
  Tuple sphere_to_ray = r.get_origin() - point(0, 0, 0);
  float a = r.get_direction().dot(r.get_direction());
  float b = 2 * r.get_direction().dot(sphere_to_ray);
  float c = sphere_to_ray.dot(sphere_to_ray) - 1;

  float discriminant = (b * b) - (4 * a * c);

  if (discriminant < 0) {
    // No intersection, return Intersection of len 0
    return Intersections();
  };
  // At least 1 intersection
  return Intersections(std::vector<Intersection>{
      Intersection((-b - std::sqrt(discriminant)) / (2 * a), this),
      Intersection((-b + std::sqrt(discriminant)) / (2 * a), this)});
};

Sphere glass_sphere(Matrix m, float refractive_index, float reflective) {
  return Sphere(m, Material(NULL, Color(1, 1, 1), 0.1, 0.1, 0.1, 300.0,
                            reflective, 1.0, refractive_index));
};
