#include <bits/stdc++.h>
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
signed main()
{
    int x;
    std::cin >> x;
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(1, 100);

    // x = dis(gen);
    // std::cout << "Generated number: " << x << std::endl;
    if (isPrime(x))
    {
        std::cout << x << " is a prime number." << std::endl;
    }
    else
    {
        std::cout << x << " is not a prime number." << std::endl;
    }

    return 0;
}