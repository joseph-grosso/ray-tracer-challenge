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

#include <vector>
#include <bits/stdc++.h> 


World::World(std::vector<Sphere> objects, std::vector<PointLight> lights) {
    this->objects = objects;
    this->lights = lights;
};

Intersections World::intersect_world(Ray r) {
    std::vector<Intersection> initial_intersections;
    Intersections i_inter;
    for (int i=0; i<objects.size(); i++) {
        i_inter = intersect(objects[i], r);
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


World default_world() {
    PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1 = Sphere(1);
    s1.set_material(
        Material(
            Color(0.8, 1.0, 0.6),  // color
            0.1,  // ambient
            0.7,  // diffuse
            0.2,  // specular
            200.0  // shininess
        )
    );
    Sphere s2 = Sphere(2);
    s2.set_transform(scaling_matrix(0.5, 0.5, 0.5));    
    return World(
        std::vector<Sphere>{s1, s2},
        std::vector<PointLight>{light}
    );
};
