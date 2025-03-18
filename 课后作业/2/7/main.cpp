#include <iostream>
using namespace std;

int main() {
    // Using for loop
    for (int n = 100; n <= 200; n += 2) {
        cout << "n = " << n << endl;
    }

    // Using while loop
    int n = 100;
    while (n <= 200) {
        cout << "n = " << n << endl;
        n += 2;
    }

    // Using do-while loop
    n = 100;
    do {
        cout << "n = " << n << endl;
        n += 2;
    } while (n <= 200);

    return 0;
}