#include <iostream>
using namespace std;

// 定义基类 BaseClass
class BaseClass
{
public:
    virtual void fn1()
    {
        cout << "BaseClass::fn1()" << endl;
    }

    void fn2()
    {
        cout << "BaseClass::fn2()" << endl;
    }
};

// 定义派生类 DerivedClass
class DerivedClass : public BaseClass
{
public:
    void fn1() override
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
    // 创建DerivedClass对象
    DerivedClass derived;

    // 用BaseClass指针指向DerivedClass对象（父指子）
    BaseClass *basePtr = &derived;

    // 用DerivedClass指针指向DerivedClass对象
    DerivedClass *derivedPtr = &derived;

    // 通过BaseClass指针调用函数
    cout << "通过BaseClass指针调用:" << endl;
    basePtr->fn1(); // 由于fn1是虚函数，将调用DerivedClass::fn1()
    basePtr->fn2(); // 由于fn2不是虚函数，将调用BaseClass::fn2()

    // 通过DerivedClass指针调用函数
    cout << "\n通过DerivedClass指针调用:" << endl;
    derivedPtr->fn1(); // 调用DerivedClass::fn1()
    derivedPtr->fn2(); // 调用DerivedClass::fn2()

    return 0;
}