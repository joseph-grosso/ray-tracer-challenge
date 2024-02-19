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

    return 0;
}
