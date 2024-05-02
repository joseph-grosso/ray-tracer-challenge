#pragma once

#include "tuple.h"


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
