#include <iostream>
#include <stdexcept>
#include <string>
class A
{
public:
    A() {}
    virtual ~A() {}
    virtual void message() const
    {
        std::cout << "异常类型: A" << std::endl;
    }
};
class B : public A
{
public:
    B() : A() {}
    ~B() override {}
    void message() const override
    {
        std::cout << "异常类型: B" << std::endl;
    }
};
class C : public B
{
public:
    C() : B() {}
    ~C() override {}
    void message() const override
    {
        std::cout << "异常类型: C" << std::endl;
    }
};
void fun(int type)
{
    std::cout << "fun函数调用，抛出类型: ";
    switch (type)
    {
    case 1:
        std::cout << "A" << std::endl;
        throw A();
    case 2:
        std::cout << "B" << std::endl;
        throw B();
    case 3:
        std::cout << "C" << std::endl;
        throw C();
    default:
        std::cout << "未抛出异常" << std::endl;
        break;
    }
}

int main()
{
    // 测试抛出 A 类型异常
    std::cout << "\n===== 测试抛出 A 类型异常 =====" << std::endl;
    try
    {
        fun(1);
    }
    catch (const A &a)
    {
        std::cout << "捕获到了 ";
        a.message();
    }
    catch (const B &b)
    {
        std::cout << "捕获到了 ";
        b.message();
    }
    catch (const C &c)
    {
        std::cout << "捕获到了 ";
        c.message();
    }

    // 测试抛出 B 类型异常
    std::cout << "\n===== 测试抛出 B 类型异常 =====" << std::endl;
    try
    {
        fun(2);
    }
    catch (const A &a)
    {
        std::cout << "捕获到了 ";
        a.message();
    }
    catch (const B &b)
    {
        std::cout << "捕获到了 ";
        b.message();
    }
    catch (const C &c)
    {
        std::cout << "捕获到了 ";
        c.message();
    }

    // 测试抛出 C 类型异常
    std::cout << "\n===== 测试抛出 C 类型异常 =====" << std::endl;
    try
    {
        fun(3);
    }
    catch (const A &a)
    {
        std::cout << "捕获到了 ";
        a.message();
    }
    catch (const B &b)
    {
        std::cout << "捕获到了 ";
        b.message();
    }
    catch (const C &c)
    {
        std::cout << "捕获到了 ";
        c.message();
    }

    return 0;
}