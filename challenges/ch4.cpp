#include <iostream>
#include <cmath>
#include <iomanip>

#include "tuple.h"
#include "canvas.h"
#include "matrix.h"
#include "transform.h"


// using namespace std;

// void fill_in_canvas_at_position(Canvas c, int x, int y) {
//     cout << "Filling canvas at position" << endl;
//     cout << "i value: " << to_string(x) << endl;
//     cout << "j value: " << to_string(y) << endl;
//     for (int i = x; i<=x+5; i++) {
//         for (int j = y; j<=y+5; j++) {
//             if (i >= 0 && i < c.get_width() && j >= 0 && j < c.get_height()) {
//                 c.write_pixel(Color(1, 0, 0), x, c.get_height() - y);
//             };
//         };
//     };
// }

int main() {

    float pi = 3.14159;
    Tuple pos = point(1, 0, 0);
    Tuple canvas_pos;

    Matrix one_clock_turn = rotation_z_matrix(pi / 6);
    Matrix map_to_canvas = translation_matrix(50, 50, 0) * scaling_matrix(40, 40, 0);

    Canvas c(100, 100);

    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "New clock starting!" << std::endl;

    for (int i=0; i < 12; i++) {
        // Remap current point to canvas_pos
        canvas_pos = map_to_canvas * pos;
        // Fill in canvas at the canvas coords
        c.write_pixel(Color(1, 1, 1), canvas_pos.x, canvas_pos.y);
        // Rotate base position
        pos = one_clock_turn * pos;
    };

    std::string filename = "clock_value.ppm";
    c.write_to_ppm(filename);

    std::cout << "Charted at " << filename << std::endl;

    return 0;
}
