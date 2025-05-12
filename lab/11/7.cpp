#include <bits/stdc++.h>
using namespace std;
double square(double x)
{
    return x * x;
}
signed main()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[sizeof(a) / sizeof(a[0])];
    transform(a, a + sizeof(a) / sizeof(a[0]), b, square);
    for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++)
        cout << b[i] << "\t";
    cout << endl;
    return 0;
}