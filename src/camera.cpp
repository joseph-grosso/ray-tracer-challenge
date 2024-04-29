#include "tuple.h"
#include "matrix.h"
#include <vector>
#include <string>
#include <math.h>

#include <iostream>

#include "camera.h"


Camera::Camera(unsigned int hsize, unsigned int vsize, float field_of_view) {
    // Computed values
    float half_view = tan(field_of_view / 2);
    float aspect = (float) hsize / vsize;


    
    if (aspect >= 1) {
        this->half_width = half_view;
        this->half_height = half_view / aspect;
    } else {
        this->half_width = half_view * aspect;
        this->half_height = half_view;
    };

    this->pixel_size = (this->half_width * 2) / hsize;

    // Raw values
    this->hsize = hsize;
    this->vsize = vsize;
    this->field_of_view = field_of_view;
};
