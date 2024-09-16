#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "matrix.h"
#include "sphere.h"
#include "lights.h"
#include "world.h"
#include "transform.h"
#include "intersection.h"
#include "intersections.h"
#include "computation.h"

#include <vector>
#include <bits/stdc++.h> 
#include <iostream>


World::World(std::vector<Sphere> objects, std::vector<PointLight> lights) {
    this->objects = objects;
    this->lights = lights;
};

Intersections World::intersect_world(Ray r) {
    std::vector<Intersection> initial_intersections;
    Intersections i_inter;
    for (int i=0; i<objects.size(); i++) {
        i_inter = objects[i].intersect(r);
        for (int j=0; j<i_inter.data.size(); j++) {
            initial_intersections.push_back(i_inter.data[j]);
        }
    }
    std::sort(
        initial_intersections.begin(),
        initial_intersections.end()
    );
    return Intersections(initial_intersections);
};

Color World::shade_hit(Computation comp) {
    bool shadowed = is_shadowed(comp.over_point);
    return (*comp.object).get_material().lighting(
        lights[0],  // TODO: Fix this when using multiple light sources! Extra chapter
        comp.over_point,
        comp.eyev,
        comp.normalv,
        shadowed
    );
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
    Sphere s1 = Sphere();
    s1.set_material(
        Material(
            Color(0.8, 1.0, 0.6),  // color
            0.1,  // ambient
            0.7,  // diffuse
            0.2,  // specular
            200.0  // shininess
        )
    );
    Sphere s2 = Sphere();
    s2.set_transform(scaling_matrix(0.5, 0.5, 0.5));
    return World(
        std::vector<Sphere>{s1, s2},
        std::vector<PointLight>{light}
    );
};

Color World::color_at(Ray r) {
    Intersections i = intersect_world(r);
    Intersection h = i.hit();

    if (h.is_empty()) {
        return Color();
    };

    Computation comp = prepare_computations(h, r);

    return shade_hit(comp);
};
