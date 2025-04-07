#include <iostream>
class A
{
public:
    void fn1()
    {
        std::cout << "基类A的fn1()函数" << std::endl;
    }

    void fn2()
    {
        std::cout << "基类A的fn2()函数" << std::endl;
    }
};

class B : public A
{
public:
    // 重载基类的fn1函数
    void fn1()
    {
        std::cout << "派生类B的fn1()函数" << std::endl;
    }

    // 在派生类的函数中调用基类函数
    void callBaseFunctions()
    {
        // 调用基类的fn1
        A::fn1();
        // 调用基类的fn2(未被重载)
        fn2();
    }
};

signed main()
{
    B b;
    b.fn1();               // 调用派生类的fn1
    b.fn2();               // 调用基类的fn2
    b.callBaseFunctions(); // 调用包含基类函数调用的函数

    return 0;
}