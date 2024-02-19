#include <iostream>

#include "tuple.h"

using namespace std;



int main() {
    // Tests the rest of the code

    // Scenario: A tuple with w=1.0 is a point
    // page 4
    Tuple a(4.3, -4.2, 3.1, 1.0);

    cout << equalByEpsilon(a.x, 4.3) << endl;
    cout << equalByEpsilon(a.y, -4.2) << endl;
    cout << equalByEpsilon(a.z, 3.1) << endl;
    cout << equalByEpsilon(a.w, 1.0) << endl;
    cout << a.isPoint() << endl;
    cout << !a.isVector() << endl;


    // Scenario: A tuple with w=0 is a vector
    // page 4
    Tuple b(4.3, -4.2, 3.1, 0.0);

    cout << equalByEpsilon(b.x, 4.3) << endl;
    cout << equalByEpsilon(b.y, -4.2) << endl;
    cout << equalByEpsilon(b.z, 3.1) << endl;
    cout << equalByEpsilon(b.w, 0) << endl;
    cout << !b.isPoint() << endl;
    cout << b.isVector() << endl;

    // Scenario: point() creates tuples with w=1
    // p4
    Tuple p = point(4, -4, 3);
    Tuple expected_point = Tuple(4, -4, 3, 1);
    cout << (expected_point == p) << endl;

    // Scenario: vector() creates tuples with w=0
    // p4
    Tuple v = vector(4, -4, 3);
    Tuple expected_vector = Tuple(4, -4, 3, 0);
    cout << (expected_vector == v) << endl;

    // Scenario: Adding two tuples
    // p6
    Tuple a1(3, -2, 5, 1);
    Tuple a2(-2, 3, 1, 0);
    Tuple actual = a1 + a2;
    Tuple expected(1, 1, 6, 1);
    cout << (expected == actual) << endl;

    // Scenario: Subtracting two points
    // p6
    Tuple b1 = point(3, 2, 1);
    Tuple b2 = point(5, 6, 7);
    Tuple actual_2 = b1 - b2;
    Tuple expected_2 = vector(-2, -4, -6);
    cout << (expected_2 == actual_2) << endl;

    // Scenario: Subtracting a vector from a point
    // p6
    Tuple p1 = point(3, 2, 1);
    Tuple v1 = vector(5, 6, 7);
    Tuple actual_3 = p1 - v1;
    Tuple expected_3 = point(-2, -4, -6);
    cout << (actual_3 == expected_3) << endl;

    // Scenario: Subtracting two vectors
    // p7
    Tuple v_1 = vector(3, 2, 1);
    Tuple v_2 = vector(5, 6, 7);
    Tuple actual_4 = v_1 - v_2;
    Tuple expected_4 = vector(-2, -4, -6);
    cout << (actual_4 == expected_4) << endl;

    // Scenario: Subtracting a vector from the zero vector
    // p7
    Tuple zero = vector(0, 0, 0);
    Tuple v_3 = vector(1, -2, 3);
    Tuple actual_5 = zero - v_3;
    Tuple expected_5 = vector(-1, 2, -3);
    cout << (actual_5 == expected_5) << endl;

    // Scenario: Negating a tuple
    Tuple a3(1, -2, 3, -4);
    Tuple actual_6 = -a3;
    Tuple expected_6(-1, 2, -3, 4);
    cout << (actual_6 == expected_6) << endl;


    cout << "End tests" << endl;
    return 0;

}
