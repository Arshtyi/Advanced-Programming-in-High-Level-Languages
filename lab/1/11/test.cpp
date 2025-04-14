#include <iostream>
#include <bitset>

using namespace std;

void printBinaryBits(int number) {
    bitset<32> bits(number);
    cout << "Binary representation of " << number << " is: " << bits << endl;
}

int main() {
    int number;
    cout << "Enter an integer: ";
    cin >> number;
    printBinaryBits(number);
    return 0;
}