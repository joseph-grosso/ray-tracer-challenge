#pragma once

#include "tuple.h"
#include "lights.h"
#include "stripe_pattern.h"

#include <cmath>

class Shape;

class Material {
    public:
        Material(
            StripePattern * pattern = NULL,
            Color color = Color(1, 1, 1),
            float ambient = 0.1,
            float diffuse = 0.9,
            float specular = 0.9,
            float shininess = 200.0
        );
        Material(
            Color color,
            float ambient,
            float diffuse,
            float specular,
            float shininess
        ) : Material(
            NULL,
            color,
            ambient,
            diffuse,
            specular,
            shininess
        ) {};
        StripePattern * pattern;
        Color color;
        float ambient;
        float diffuse;
        float specular;
        float shininess;
        std::string to_string();
        Color lighting(
            Shape * object,
            PointLight light,
            Tuple position,
            Tuple eyev,
            Tuple normalv,
            bool in_shadow
        );
};

bool operator==(Material lhs, Material rhs);