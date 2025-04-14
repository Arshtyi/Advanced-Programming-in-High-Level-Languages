#include <iostream>

#include "point.h"

using namespace std;

// 主程序

int main()
{

    Point a(4, 5); // 构造第一个对象a

    Point b = a; // 情况一，用a初始化b。第一次调用复制构造函数，等价于b(a)

    // 注：此处不是赋值运算，与单独b=a不同，不调用=运算符重载。

    cout << b.getX() << endl;

    fun1(b); // 情况二，对象B作为fun1的实参。第二次调用复制构造函数

    b = fun2(); // 情况三，函数的返回值是类对象，函数返回时调用复制构造函数

    // 注：vc调用复制构造函数，但其他编译器优化成调用=运算符重载

    cout << b.getX() << endl;

    return 0;
}