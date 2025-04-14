#include <bits/stdc++.h>
using namespace std;

int64_t sum(int64_t n)
{
    return n ? n + sum(n - 1) : 0;
}
signed main()
{
    int64_t x;
    cout << "请输入：\n";
    cin >> x;
    cout << "求和结果为: " << sum(x) << endl;
    return 0;
}