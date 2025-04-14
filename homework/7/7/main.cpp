#include <iostream>
using namespace std;

// 定义基类
class Base
{
public:
    Base()
    {
        cout << "Base类的构造函数被调用" << endl;
    }
};

// 定义派生类
class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived类的构造函数被调用" << endl;
    }
};

int main()
{
    cout << "创建Derived类对象..." << endl;
    Derived obj; // 构造派生类对象
    return 0;
}