#include <iostream>
using namespace std;

// main() is where program execution begins.
int main() {
    int x, y, sum;
    cout << "Type a number: ";
    cin >> x;
    cout << "Typed Num: " << x << endl; 
    cout << "Type another number: ";
    cin >> y;
    cout << "Typed Num: " << y << endl; 
    sum = x + y;
    cout << "Sum: " << sum << endl;
    return 0;
}