#include <iostream>

using namespace std;

int sumOfSquare(int a, int b = 1)
{

    return a * a + b * b;
}

int sumOfSquare(int a)
{

    return a * a;
}

double sumOfSquare(double a, double b)
{

    return a * a + b * b;
}

int main()
{

    int m, n;

    cout << "Enter two integer: ";

    cin >> m >> n;

    cout << "Their sum of square: " << sumOfSquare(m, n) << endl;

    cout << "Their sum of square: " << sumOfSquare(m) << endl;

    double x, y;

    cout << "Enter two real number: ";

    cin >> x >> y;

    cout << "Their sum of square: " << sumOfSquare(x, y) << endl;

    return 0;
}
