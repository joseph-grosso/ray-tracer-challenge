#pragma once

#include "tuple.h"
#include "matrix.h"
#include <vector>
#include <string>


// Chapter 7: Making a Scene
class Camera {
    public:
        // Attributes
        float half_width;
        float half_height;
        unsigned int hsize;
        unsigned int vsize;
        float field_of_view;
        Matrix transform;
        float pixel_size;
        // Methods
        Camera(unsigned int hsize, unsigned int vsize, float field_of_view);
};
