#include <iostream>
using namespace std;

// 第一个类，带有普通函数
class Class1
{
public:
    int i;
    void fun()
    {
        cout << "Class1::fun()" << endl;
    }
};

// 第二个类，带有虚函数
class Class2
{
public:
    int i;
    virtual void fun()
    {
        cout << "Class2::fun()" << endl;
    }
};

int main()
{
    // 定义对象
    Class1 obj1;
    Class2 obj2;

    // 输出对象大小
    cout << "Class1对象的大小: " << sizeof(obj1) << " 字节" << endl;
    cout << "Class2对象的大小: " << sizeof(obj2) << " 字节" << endl;

    // 比较大小并解释
    if (sizeof(obj1) < sizeof(obj2))
    {
        cout << "Class1对象比Class2对象小" << endl;
    }
    else if (sizeof(obj1) > sizeof(obj2))
    {
        cout << "Class1对象比Class2对象大" << endl;
    }
    else
    {
        cout << "Class1对象和Class2对象大小相同" << endl;
    }

    return 0;
}