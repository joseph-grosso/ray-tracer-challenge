#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "shape.h"
#include "lights.h"
#include "intersection.h"
#include "intersections.h"
#include "computation.h"
#include "color.h"
#include "transform.h"

#include <vector>
#include <bits/stdc++.h> 
#include <iostream>


class World {
    public:
        std::vector<Shape *> objects;
        std::vector<PointLight> lights;
        World(std::vector<Shape *> objects = std::vector<Shape *>{}, std::vector<PointLight> lights = std::vector<PointLight>{});
        World(Shape * s, PointLight l) : World(std::vector<Shape *> (1, s), std::vector<PointLight> {1, l})  {};
        World(std::vector<Shape *> s_list, PointLight l) : World(s_list, std::vector<PointLight> {1, l})  {};
        Intersections intersect_world(Ray r);
        Color shade_hit(Computation comp);
        Color color_at(Ray r);
        bool is_shadowed(Tuple p);
};

World default_world();