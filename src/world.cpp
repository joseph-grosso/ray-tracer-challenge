#include "world.hpp"

#include "sphere.hpp"

World::World(std::vector<Shape *> objects, std::vector<PointLight> lights) {
  this->objects = objects;
  this->lights = lights;
};

Intersections World::intersect_world(Ray r) {
  std::vector<Intersection> initial_intersections;
  Intersections i_inter;
  for (int i = 0; i < objects.size(); i++) {
    i_inter = (*objects[i]).intersect(r);
    for (int j = 0; j < i_inter.data.size(); j++) {
      initial_intersections.push_back(i_inter.data[j]);
    }
  }
  std::sort(initial_intersections.begin(), initial_intersections.end());
  return Intersections(initial_intersections);
};

Color World::shade_hit(Computation comp, int remaining) {
  bool shadowed = is_shadowed(comp.over_point);
  Color surface = (*comp.object)
                      .get_material()
                      .lighting(comp.object, lights[0], comp.over_point,
                                comp.eyev, comp.normalv, shadowed);
  Color reflected = reflected_color(comp, remaining);
  Color refracted = refracted_color(comp, remaining);
  // Fresnel effect
  if (comp.object->get_material().reflective > 0 &&
      comp.object->get_material().transparency > 0) {
    float reflectance = comp.schlick();
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  };
  return surface + reflected + refracted;
};

// p113
bool World::is_shadowed(Tuple p) {
  // TODO: replace with multiple light sources
  Tuple direction = lights[0].get_position() - p;
  float distance = direction.magnitude();
  Ray r(p, direction.normalize());

  Intersections i = intersect_world(r);
  Intersection hit = i.hit();

  return !hit.is_empty() && hit.t < distance;
};

World default_world() {
  PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));
  Shape *s1 = new Sphere();
  (*s1).set_material(Material(Color(0.8, 1.0, 0.6),  // color
                              0.1,                   // ambient
                              0.7,                   // diffuse
                              0.2,                   // specular
                              200.0                  // shininess
                              ));
  Shape *s2 = new Sphere();
  (*s2).set_transform(scaling_matrix(0.5, 0.5, 0.5));
  return World(std::vector<Shape *>{s1, s2}, std::vector<PointLight>{light});
};

Color World::color_at(Ray r, int remaining) {
  Intersections i = intersect_world(r);
  Intersection h = i.hit();

  if (h.is_empty()) {
    return Color();
  };

  Computation comp = h.prepare_computations(r, i);

  return shade_hit(comp, remaining);
};

Color World::reflected_color(Computation comp, int remaining) {
  if (equalByEpsilon(comp.object->get_material().reflective, 0) ||
      remaining <= 0) {
    return Color(0, 0, 0);
  };

  Ray reflected_ray = Ray(comp.over_point, comp.reflectv);
  Color col = color_at(reflected_ray, remaining - 1);

  return col * comp.object->get_material().reflective;
};

Color World::refracted_color(Computation comps, int remaining) {
  // uses Snell's Law to describe the relationship between the angle of the
  // incoming ray and the angle of the refracted ray. See below for equation:
  // sin(theta_i)    n_2
  // ------------ == ---
  // sin(theta_t)    n_1
  float n_ratio = comps.n1 / comps.n2;
  float cos_i = comps.eyev.dot(comps.normalv);
  float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
  if (comps.object->get_material().transparency == 0 || remaining <= 0 ||
      sin2_t > 1) {
    return Color(0, 0, 0);
  };

  // Find cos(theta_t) via trigonometric identity
  float cos_t = std::sqrt(1.0 - sin2_t);
  // compute the direction of the refracted ray
  Tuple direction =
      comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;
  // Create the refracted ray
  Ray refract_ray = Ray(comps.under_point, direction);
  // Find the color of the refracted ray, maing sure to mutliply by the
  // transparency value to account for any opacity
  return color_at(refract_ray, remaining - 1) *
         comps.object->get_material().transparency;
};

float World::calculate_angle_ratio(Computation comps) {
  float n_ratio = comps.n1 / comps.n2;
  float cos_i = comps.eyev.dot(comps.normalv);
  return n_ratio * n_ratio * (1 - cos_i * cos_i);
}