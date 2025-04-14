#include <bits/stdc++.h>
using namespace std;
class Complex
{
private:
    double x, y;

public:
    Complex(double x = 0, double y = 0) : x(x), y(y) {}
    Complex operator+(const Complex &other) const
    {
        return Complex(x + other.x, y + other.y);
    }
    Complex operator+(const double &db) const
    {
        return Complex(x + db, y);
    }
    Complex operator-(const Complex &other) const
    {
        return Complex(x - other.x, y - other.y);
    }
    Complex operator=(const Complex &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    void display() const
    {
        cout << x << " + " << y << "i" << endl;
    }
};
signed main()
{
    Complex c1(5, 4), c2(2, 10), c3 = c1 + 0.5;
    c3.display();

    return 0;
}