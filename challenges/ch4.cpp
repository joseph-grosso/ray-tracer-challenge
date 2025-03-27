#include <cmath>
#include <iomanip>
#include <iostream>

#include "canvas.h"
#include "matrix.h"
#include "transform.h"
#include "tuple.h"

// using namespace std;

// void fill_in_canvas_at_position(Canvas c, int x, int y) {
//     cout << "Filling canvas at position" << endl;
//     cout << "i value: " << to_string(x) << endl;
//     cout << "j value: " << to_string(y) << endl;
//     for (int i = x; i<=x+5; i++) {
//         for (int j = y; j<=y+5; j++) {
//             if (i >= 0 && i < c.get_width() && j >= 0 && j < c.get_height())
//             {
//                 c.write_pixel(Color(1, 0, 0), x, c.get_height() - y);
//             };
//         };
//     };
// }

int main() {
  float pi = 3.14159;
  Tuple pos = point(1, 0, 0);
  Tuple canvas_pos;
  Tuple reflected_canvas_pos;

  Matrix one_clock_turn = rotation_z_matrix(-pi / 100);
  Matrix map_to_canvas =
      translation_matrix(30, 50, 0) * scaling_matrix(20, 20, 0);

  Canvas c(100, 100);

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "New clock starting!" << std::endl;

  // top
  for (int i = 0; i <= 100; i++) {
    // Remap current point to canvas_pos
    canvas_pos = map_to_canvas * pos;
    reflected_canvas_pos = translation_matrix(40, 0, 0) * canvas_pos;
    // Fill in canvas at the canvas coords
    c.write_pixel(Color(1, 0, 0), canvas_pos.x(), canvas_pos.y());
    c.write_pixel(Color(1, 0, 0), reflected_canvas_pos.x(),
                  reflected_canvas_pos.y());
    // Rotate base position
    pos = one_clock_turn * pos;
  };

  // bottom left
  Tuple line_pos = point(0, 0, 0);
  int movement_factor = 10;
  map_to_canvas = translation_matrix(10, 50, 0);
  Matrix movement = translation_matrix(1, 1, 0);
  for (int i = 0; i <= 40; i++) {
    // Remap current point to canvas_pos
    canvas_pos = map_to_canvas * line_pos;
    reflected_canvas_pos = translation_matrix(40, 0, 0) * canvas_pos;
    // Fill in canvas at the canvas coords
    c.write_pixel(Color(1, 0, 0), canvas_pos.x(), canvas_pos.y());
    // Move base position
    line_pos = movement * line_pos;
  };

  // bottom right
  line_pos = point(0, 0, 0);
  map_to_canvas = translation_matrix(89, 50, 0);
  movement = translation_matrix(-1, 1, 0);
  for (int i = 0; i <= 40; i++) {
    // Remap current point to canvas_pos
    canvas_pos = map_to_canvas * line_pos;
    reflected_canvas_pos = translation_matrix(40, 0, 0) * canvas_pos;
    // Fill in canvas at the canvas coords
    c.write_pixel(Color(1, 0, 0), canvas_pos.x(), canvas_pos.y());
    // Move base position
    line_pos = movement * line_pos;
  };
  std::string filename = "heart.ppm";
  c.write_to_ppm(filename);

  std::cout << "Charted at " << filename << std::endl;

  return 0;
}

// float pi = 3.14159;
// Canvas c(100, 100);

// std::cout << std::setprecision(2) << std::fixed;
// std::cout << "New clock starting!" << std::endl;

// Tuple canvas_pos;

// // top
// Tuple pos_circles = point(1, 0, 0);
// Matrix scale = translation_matrix(20, -50, 0) * scaling_matrix(20, 20, 0);
// Matrix one_of_10_rotations = rotation_z_matrix(1 / 10);
// for (int i=0; i < 10; i++) {
//     // Remap current point to canvas_pos
//     canvas_pos = scale * pos_circles;
//     // Fill in canvas at the canvas coords
//     c.write_pixel(Color(1, 0, 0), canvas_pos.x(), canvas_pos.y());
//     // Rotate base position
//     pos_circles = one_of_10_rotations * pos_circles;
// };
