#include "myostream.hpp"
myostream myout;
int main()
{
    myout << "Hello, World!" << '\n';
    myout.setw(10).left() << 123 << '\n';
    myout.setw(10).right() << 456 << '\n';
    myout.setprecision(2) << 3.14159 << '\n';
    myout.setw(15).setprecision(4).right() << 2.71828 << '\n';
    myout.reset() << "Back to default" << '\n';
    return 0;
}