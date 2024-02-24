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

    // Scenario: test getting heights and widths
    // pMe
    Canvas canvas(1, 2);
    cout << (canvas.get_width() == 1) << endl;
    cout << (canvas.get_height() == 2) << endl;

    // scenario: Test canvas points
    Canvas canvas_1(5, 10);
    cout << (canvas.get_point(3, 8) == Color(0, 0, 0)) << endl;
    

    cout << "End tests" << endl;
    return 0;
}
