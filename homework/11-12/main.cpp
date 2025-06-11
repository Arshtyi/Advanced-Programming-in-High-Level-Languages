#include <iostream>
using namespace std;
int divide(int a, int b)
{
    if (b == 0)
    {
        throw "除数不能为零！"; // throw 抛出异常
    }
    return a / b;
}

int main()
{
    try
    { // try 块，放置可能抛出异常的代码
        int x = 10, y = 0;
        int result = divide(x, y);
        cout << "结果: " << result << endl;
    }
    catch (const char *msg)
    { // catch 块，捕获并处理异常
        cout << "捕获到异常: " << msg << endl;
    }
    return 0;
}
