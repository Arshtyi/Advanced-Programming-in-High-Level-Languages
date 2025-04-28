#include <iostream>
using namespace std;

template <class T, int N>
void outputArray(const T (&array)[N])
{
    for (int i = 0; i < N; i++)
        cout << array[i] << " ";
    cout << endl;
}

int main()
{ // 主函数
    const int A_COUNT = 8, B_COUNT = 8, C_COUNT = 20;
    int a[A_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8};                    // 定义int数组
    double b[B_COUNT] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8}; // 定义double数组
    char c[C_COUNT] = "Welcome to see you!";                      // 定义char数组

    cout << " a array contains:" << endl;
    outputArray(a); // 调用函数模板,int
    cout << " b array contains:" << endl;
    outputArray(b); // 调用函数模板，double
    cout << " c array contains:" << endl;
    outputArray(c); // 调用函数模板，char
    return 0;
}