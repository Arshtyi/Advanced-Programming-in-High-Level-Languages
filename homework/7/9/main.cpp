#include <iostream>
using namespace std;

class Base
{
public:
    void fn1()
    {
        cout << "Base::fn1() called" << endl;
    }
};

class Derived : private Base
{
public:
    using Base::fn1;
};

int main()
{
    Derived obj;
    obj.fn1();
    return 0;
}