#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "lights.h"
#include "intersection.h"
#include "computation.h"

#include <vector>


class World {
    public:
        std::vector<Sphere> objects;
        std::vector<PointLight> lights;
        World(std::vector<Sphere> objects = std::vector<Sphere>{}, std::vector<PointLight> lights = std::vector<PointLight>{});
        World(Sphere s, PointLight l) : World(std::vector<Sphere> (1, s), std::vector<PointLight> {1, l})  {};
        World(std::vector<Sphere> s_list, PointLight l) : World(s_list, std::vector<PointLight> {1, l})  {};
        Intersections intersect_world(Ray r);
        Color shade_hit(Computation comp);
};

World default_world();