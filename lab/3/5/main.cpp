#include <iostream>

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

T func1(T a)
{
   // cout << 1 << endl;
    return a;
}

T func2(T a)
{
    //cout << 2 << endl;
    return T(a);
}

T func3(T a)
{

    //cout << 3 << endl;
    T b = a;

    return b;
}

// 主程序

int main()
{

    T a;

    T c = func1(a);
    T d = func2(a);
    T e = func3(a);

    return 0;
}