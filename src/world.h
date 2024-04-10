#pragma once

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"

#include <vector>
#include <random> 


class World {
    public:
        std::vector<Sphere> objects;
        std::vector<PointLight> lights;
        World(std::vector<Sphere>, std::vector<PointLight>);
        World(Sphere, PointLight);
        World(std::vector<Sphere>, PointLight);
};

