#include "transform.hpp"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "matrix.hpp"
#include "tuple.hpp"

// Chapter 4: Matrix Transformations
// Transformations
Matrix translation_matrix(float x, float y, float z) {
  std::vector<float> translation_data = {1, 0, 0, x, 0, 1, 0, y,
                                         0, 0, 1, z, 0, 0, 0, 1};
  return Matrix(4, 4, translation_data);
};

Matrix scaling_matrix(float x, float y, float z) {
  std::vector<float> scaling_data = {x, 0, 0, 0, 0, y, 0, 0,
                                     0, 0, z, 0, 0, 0, 0, 1};
  return Matrix(4, 4, scaling_data);
};

Matrix rotation_x_matrix(float radians) {
  std::vector<float> rotate_data = {1,
                                    0,
                                    0,
                                    0,
                                    0,
                                    std::cos(radians),
                                    -std::sin(radians),
                                    0,
                                    0,
                                    std::sin(radians),
                                    std::cos(radians),
                                    0,
                                    0,
                                    0,
                                    0,
                                    1};
  return Matrix(4, 4, rotate_data);
};
Matrix rotation_y_matrix(float radians) {
  std::vector<float> rotate_data = {
      std::cos(radians),  0, std::sin(radians), 0, 0, 1, 0, 0,
      -std::sin(radians), 0, std::cos(radians), 0, 0, 0, 0, 1};
  return Matrix(4, 4, rotate_data);
};
Matrix rotation_z_matrix(float radians) {
  std::vector<float> rotate_data = {std::cos(radians),
                                    -std::sin(radians),
                                    0,
                                    0,
                                    std::sin(radians),
                                    std::cos(radians),
                                    0,
                                    0,
                                    0,
                                    0,
                                    1,
                                    0,
                                    0,
                                    0,
                                    0,
                                    1};
  return Matrix(4, 4, rotate_data);
};
Matrix shearing_matrix(float x_y, float x_z, float y_x, float y_z, float z_x,
                       float z_y) {
  std::vector<float> shear_data = {1,   x_y, x_z, 0, y_x, 1, y_z, 0,
                                   z_x, z_y, 1,   0, 0,   0, 0,   1};
  return Matrix(4, 4, shear_data);
};

// Chapter 7: Making a Scene
// Defining a view transform
Matrix view_transform(Tuple from, Tuple to, Tuple up) {
  // Compute "forward" direction and normalize
  Tuple forward = (to - from).normalize();
  // Compute normalized up vector
  Tuple upn = up.normalize();
  // Compute "left" with the cross product
  Tuple left = forward.cross(upn);
  // Compute "true up" with the cross of left and forward
  Tuple true_up = left.cross(forward);
  // Create the orientation matrix using computed vectors
  Matrix orientation(4, 4,
                     std::vector<float>{left.x, left.y, left.z, 0, true_up.x,
                                        true_up.y, true_up.z, 0, -forward.x,
                                        -forward.y, -forward.z, 0, 0, 0, 0, 1});

  // Translate the scene into place before orienting it
  return orientation * translation_matrix(-from.x, -from.y, -from.z);
};
