#pragma once

#include "tuple.h"


class Material {
    public:
        Material(
            Color color = Color(1, 1, 1), 
            float ambient = 0.1,
            float diffuse = 0.9,
            float specular = 0.9,
            float shininess = 200.0
        );
        Color color;
        float ambient;
        float diffuse;
        float specular;
        float shininess;
};

bool operator==(Material lhs, Material rhs);