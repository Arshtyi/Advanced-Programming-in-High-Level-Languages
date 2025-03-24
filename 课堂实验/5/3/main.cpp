#include <iostream>

// 前向声明
class A;
class B;
class C;

// 类 C 定义
class C
{
private:
    int dataC;

public:
    C(int c) : dataC(c) {}

    void printC()
    {
        std::cout << "C: " << dataC << std::endl;
    }

    // 声明 B 为友元
    friend class B;
};

// 类 B 定义
class B
{
private:
    int dataB;

public:
    B(int b) : dataB(b) {}

    // B 访问 C 的私有数据（合法，因为 B 是 C 的友元）
    void accessC(C &c)
    {
        std::cout << "B 访问 C: " << c.dataC << std::endl;
        // 修改 C 的私有数据
        c.dataC = 30;
        std::cout << "B 修改 C: " << c.dataC << std::endl;
    }

    // B 为 A 提供访问 C 的私有数据的接口
    int getCDataForA(C &c)
    {
        return c.dataC;
    }

    void printB()
    {
        std::cout << "B: " << dataB << std::endl;
    }

    // 声明 A 为友元
    friend class A;
};

// 类 A 定义
class A
{
private:
    int dataA;

public:
    A(int a) : dataA(a) {}

    // A 通过 B 间接访问 C 的私有数据
    void accessCThroughB(B &b, C &c)
    {
        int cData = b.getCDataForA(c);
        std::cout << "A 间接访问 C: " << cData << std::endl;
    }

    // 如果取消下面这个方法的注释，将导致编译错误
    // 证明 A 不能直接访问 C 的私有数据
    /*
    void accessCDirectly(C& c) {
        // 这行会导致编译错误，因为 A 不是 C 的友元
        std::cout << "A trying to access C's private data directly: " << c.dataC << std::endl;
    }
    */

    void printA()
    {
        std::cout << "A: " << dataA << std::endl;
    }
};

int main()
{
    A a(1);
    B b(2);
    C c(3);

    std::cout << "初始状态：" << std::endl;
    a.printA();
    b.printB();
    c.printC();

    std::cout << "\n验证友元关系：" << std::endl;

    // B 可以直接访问和修改 C 的私有数据
    b.accessC(c);

    // A 通过 B 间接访问 C 的私有数据
    a.accessCThroughB(b, c);

    std::cout << "\n结论：" << std::endl;
    std::cout << "1. B 是 C 的友元，可以直接访问 C 的私有数据。" << std::endl;
    std::cout << "2. A 是 B 的友元，但不是 C 的友元。" << std::endl;
    std::cout << "3. A 不能直接访问 C 的私有数据，只能通过 B 作为中介间接访问。" << std::endl;
    std::cout << "4. 因此，友元关系不具有传递性，'朋友的朋友不是我的朋友'在 C++ 友元关系中成立。" << std::endl;

    return 0;
}