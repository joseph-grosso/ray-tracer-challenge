#pragma once

#include "tuple.h"
#include "matrix.h"
#include <vector>
#include <string>


// Chapter 4: Matrix Transformations
// Transformations
Matrix translation(float x, float y, float z);
Matrix scaling(float x, float y, float z);
Matrix rotation_x(float radians);
Matrix rotation_y(float radians);
Matrix rotation_z(float radians);
Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
