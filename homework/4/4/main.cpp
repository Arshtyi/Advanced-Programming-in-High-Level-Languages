#include <iostream>

class A
{
public:
    int a;

    // 普通构造函数
    A(int value) : a(value) {}

    // 复制构造函数
    A(const A &other) : a(other.a)
    {
        std::cout << "Copy constructor called" << std::endl;
    }
};

void display(A obj)
{
    std::cout << "Inside display function, obj.a: " << obj.a << std::endl;
}

int main()
{
    A A1(10);
    A A2(A1); // 调用复制构造函数

    std::cout << "A1.a: " << A1.a << std::endl;
    std::cout << "A2.a: " << A2.a << std::endl;

    display(A1); // 调用复制构造函数

    return 0;
}