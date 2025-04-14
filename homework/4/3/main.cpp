#include <iostream>

class A
{
public:
    int a;
    A(int value) : a(value) {}
};

int main()
{
    A A1(10);
    A A2(20);

    std::cout << "A1.a: " << A1.a << std::endl;
    std::cout << "A2.a: " << A2.a << std::endl;

    return 0;
}