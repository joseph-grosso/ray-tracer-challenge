#include <iostream>
#include <cmath>
#include <vector>
#include "tuple.h"
#include "canvas.h"

using namespace std;



int main() {
    // Tests the rest of the code

    cout << "Test Colors" << endl;
    // Scenario: Colors are (red, green, blue) tuples
    // p16
    Color c(-0.5, 0.4, 1.7);
    cout << equalByEpsilon(c.red, -0.5f) << endl;
    cout << equalByEpsilon(c.green, 0.4f) << endl;
    cout << equalByEpsilon(c.blue, 1.7f) << endl;

    // Scenario: Adding colors
    // p17
    Color c1(0.9, 0.6, 0.75), c2(0.7, 0.1, 0.25);
    Color expected(1.6, 0.7, 1.0);
    cout << (expected == c1 + c2) << endl;

    // Scenario: Subtracting colors
    // p17
    Color c3(0.9, 0.6, 0.75), c4(0.7, 0.1, 0.25);
    Color expected_2(0.2, 0.5, 0.5);
    cout << (expected_2 == c3 - c4) << endl;

    // Scenario: Multiplying a color by a scalar
    // p17
    Color c5(0.2, 0.3, 0.4);
    Color expected_3(0.4, 0.6, 0.8);
    cout << (expected_3 == c5 * 2) << endl;
    cout << (expected_3 == 2 * c5) << endl;

    // Scenario: Multiplying two colors together
    // 
    Color c6(1, 0.2, 0.4), c7(0.9, 1, 0.1);
    cout << (Color(0.9, 0.2, 0.04) == c6 * c7) << endl;

    cout << "End test colors" << endl;

    cout << "Test canvas" << endl;
    // Scenario: test getting heights and widths
    // p19
    Canvas canvas(10, 20);
    cout << (canvas.get_width() == 10) << endl;
    cout << (canvas.get_height() == 20) << endl;

    // scenario: Writing pixels to canvas
    // p19
    Canvas canvas_1(5, 10);
    Color red(1, 0, 0), black(0, 0, 0);
    canvas_1.write_pixel(red, 3, 9);
    cout << (canvas_1.pixel_at(3, 8) == black) << endl;
    cout << (canvas_1.pixel_at(3, 9) == red) << endl;

    cout << "End Test canvas" << endl;
    cout << "Test write ppm file" << endl;

    // Scenario: Construct larger ppm file
    // p21
    Canvas canvas_3(5, 3);
    canvas_3.write_pixel(Color(1.5, 0, 0), 0, 0);
    canvas_3.write_pixel(Color(0, 0.5, 0), 2, 1);
    canvas_3.write_pixel(Color(-0.5, 0, 1), 4, 2);
    string expected_5 = "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    cout << (expected_5 == canvas_3.canvas_to_ppm()) << endl;

    // Scenario: Splitting long lines in PPM files
    // p22
    Canvas canvas_4(10, 2);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 2; j++) {
            canvas_4.write_pixel(Color(1, 0.8, 0.6), i, j);
        }
    }
    string expected_6 = "P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    cout << (canvas_4.canvas_to_ppm() == expected_6) << endl;

    // Scenario: PPM output always ends with newline
    // p22
    Canvas canvas_5(5, 3);
    string ppm = canvas_5.canvas_to_ppm();
    cout << (ppm.back() == '\n') << endl;


    // Scenario: PPM output to a file
    // pMe
    Canvas canvas_6(100, 150);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 2; j++) {
            canvas_6.write_pixel(Color(1, 0.8, 0.6), i, j);
        }
    }
    canvas_6.write_to_ppm();

    cout << "End Test write ppm file" << endl;

    cout << "End tests" << endl;
    return 0;
}
