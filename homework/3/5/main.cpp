#include <bits/stdc++.h>
short divide(unsigned short a, unsigned short b)
{
    if (b == 0)
    {
        return -1;
    }
    return static_cast<short>(a / b);
}
signed main()
{
    unsigned short a, b;
    std::cin >> a >> b;
    // std::mt19937 mt_rand(time(nullptr));
    // a = mt_rand() % 65536;
    // b = mt_rand() % 65535 + 1;
    std::cout << "a= " << a << ", b= " << b << std::endl;
    std::cout << divide(a, b) << std::endl;
    return 0;
}