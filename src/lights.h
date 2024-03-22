#pragma once

#include "tuple.h"
#include "material.h"

// Chapter 6: Lights and Shading
class PointLight {
    private:
        Tuple position;
        Color intensity;
    public:
        PointLight(Tuple position, Color intensity);
        Tuple get_position();
        Color get_intensity();
};

Color lighting(
    Material m,
    PointLight light,
    Tuple position,
    Tuple eyev,
    Tuple normalv
);
