#include <iostream>
using namespace std;

class A
{
public:
    A() { cout << "A构造函数" << endl; }
    void show() { cout << "A::show()" << endl; }
};

class B : virtual public A
{
public:
    B() { cout << "B构造函数" << endl; }
};

class C : virtual public A
{
public:
    C() { cout << "C构造函数" << endl; }
};

class D : public B, public C
{
public:
    D() { cout << "D构造函数" << endl; }
};

int main()
{
    D d;
    d.show(); // 不会有歧义，直接调用A::show()
    return 0;
}