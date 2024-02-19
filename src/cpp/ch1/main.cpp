#include <iostream>
using namespace std;

class Tuple {
    public:
        float x;  // Attribute
        float y;  // Attribute
        float z;  // Attribute
        float w;  // Attribute
        Tuple(float x, float y, float z, float w);
};

int main() {
    Tuple a(1.0, 2.0, -4.0, 0);

    cout << a.x << endl;
    cout << a.y << endl;
    cout << a.z << endl;
    cout << a.w << endl;
    return 0;
}

Tuple::Tuple(float x, float y, float z, float w) {
            this -> x = x;
            this -> y = y;
            this -> z = z;
            this -> w = w;
}
