#include <bits/stdc++.h>
inline int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

inline int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}
signed main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    int a = dis(gen);
    int b = dis(gen);

    std::cout << "Generated numbers: " << a << " and " << b << std::endl;
    std::cout << "GCD: " << gcd(a, b) << std::endl;
    std::cout << "LCM: " << lcm(a, b) << std::endl;
    return 0;
}