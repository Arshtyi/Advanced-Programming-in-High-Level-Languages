#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define notie cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define endl '\n'
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define cs const
#define db double
#define ld long double
#define fl float
#define vec vector
#define all(x) (x).begin(), (x).end()
#define int long long
#define LOCAL freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
template <typename Container>
int josephus(int n, int m)
{
    Container circle;
    FOR(i, 1, n)
    circle.pb(i);
    auto it = circle.begin();
    while (circle.size() > 1)
    {
        for (int count = 1; count < m; ++count)
        {
            ++it;
            if (it == circle.end())
                it = circle.begin();
        }
        auto next_it = next(it);
        if (next_it == circle.end())
            next_it = circle.begin();
        it = circle.erase(it);
        if (it == circle.end())
            it = circle.begin();
    }
    return circle.front();
}

void solve()
{
    int n = 5;   // 骑士数量
    int m = 1e8; // 报数值
    auto start = chrono::high_resolution_clock::now();
    int result1 = josephus<vector<int>>(n, m);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start);
    auto start2 = chrono::high_resolution_clock::now();
    int result2 = josephus<deque<int>>(n, m);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
    auto start3 = chrono::high_resolution_clock::now();
    int result3 = josephus<list<int>>(n, m);
    auto end3 = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
    cout << "约瑟夫问题: n = " << n << ", m = " << m << endl;
    cout << "vector 结果: " << result1 << ", 耗时: " << duration1.count() << " 毫秒" << endl;
    cout << "deque 结果: " << result2 << ", 耗时: " << duration2.count() << " 毫秒" << endl;
    cout << "list 结果: " << result3 << ", 耗时: " << duration3.count() << " 毫秒" << endl;
}

signed main()
{
    // LOCAL;
    notie;
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}