#include <iostream>
#include <cmath>

#include "tuple.h"

using namespace std;


bool equalByEpsilon(float a, float b, float epsilon = 0.00001) {
    // return a <= b + epsilon && a >= b - epsilon;
    return std::abs(a - b) <= epsilon;
}


int main() {
    // Tests the rest of the code

    // Scenario: A tuple with w=1.0 is a point
    // page 4
    Tuple a(4.3, -4.2, 3.1, 1.0);

    cout << equalByEpsilon(a.x, 4.3) << endl;
    cout << equalByEpsilon(a.y, -4.2) << endl;
    cout << equalByEpsilon(a.z, 3.1) << endl;
    cout << equalByEpsilon(a.w, 1.0) << endl;
    return 0;
}
