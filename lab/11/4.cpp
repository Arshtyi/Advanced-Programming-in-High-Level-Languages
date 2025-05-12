// 注意需加编译选项 -std=c++17或-std=gnu++17
#include <iostream>
template <typename T>
void print(T &t)
{ // 另一函数
    std::cout << t << std::endl;
}

template <typename T, typename... TypeArgs>
void func(const TypeArgs &...args)
{
    std::cout << sizeof...(args) << std::endl; // 参数个数
    (print(args), ...);                        // 折叠表达式，对args的每个参数调用print
}

int main()
{
    func<int>(3, 4.5, "hello world!");
    return 0;
}