#include <bits/stdc++.h>
using namespace std;
class Point
{
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }
    Point operator=(const Point &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    bool operator==(const Point &other) const
    {
        return (x == other.x && y == other.y);
    }
};
signed main()
{

    return 0;
}