#include <bits/stdc++.h>
class Counter
{
private:
    int count;

public:
    Counter() : count(0) {}
    Counter operator+(const int &n)
    {
        Counter temp;
        temp.count = this->count + n;
        return temp;
    }
    int getCount() const
    {
        return count;
    }
};
signed main()
{
    Counter c1, c2;
    c1 = c1 + 5;
    c2 = c2 + 10;
    std::cout << "Counter 1: " << c1.getCount() << std::endl;
    std::cout << "Counter 2: " << c2.getCount() << std::endl;
    return 0;
}