#include <iostream>
using namespace std;

class BaseClass
{
public:
    void fn1()
    {
        cout << "BaseClass::fn1()" << endl;
    }

    void fn2()
    {
        cout << "BaseClass::fn2()" << endl;
    }
};

class DerivedClass : public BaseClass
{
public:
    void fn1()
    {
        cout << "DerivedClass::fn1()" << endl;
    }

    void fn2()
    {
        cout << "DerivedClass::fn2()" << endl;
    }
};

int main()
{
    DerivedClass obj;

    obj.fn1();
    obj.fn2();

    BaseClass *basePtr = &obj;
    basePtr->fn1();
    basePtr->fn2();

    DerivedClass *derivedPtr = &obj;
    derivedPtr->fn1();
    derivedPtr->fn2();

    return 0;
}