#include <iostream>

// #include "point.h"

using namespace std;

class T
{

public:
    T() = default;

    T(const T &t)
    {

        cout << "construct" << endl;
    }

    T &operator=(const T &t)
    {

        cout << "assign" << endl;

        return *this;
    }
};

// 主程序

int main()
{

    T t1;
    T t2 = t1; // 调用复制构造函数
    T t3;
    t3 = t1; // 调用赋值操作符重载函数

    return 0;
}