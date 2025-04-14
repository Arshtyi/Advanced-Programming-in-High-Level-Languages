#include <bits/stdc++.h>
double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}
signed main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (int i = 0; i < 10; ++i)
    {
        double fahrenheit = dis(gen);
        double celsius = fahrenheitToCelsius(fahrenheit);
        std::cout << "华氏度: " << fahrenheit << " -> 摄氏度: " << celsius << std::endl;
    }
    return 0;
}