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
// #define int long long
#define LOCAL freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
void solve()
{
    vec<int> s; // 创建一个向量容器

    cout << "初始容量: " << s.capacity() << endl;

    FOR(i, 1, 30)
    {
        s.pb(i); // 使用 push_back 添加元素
        cout << "添加元素 " << i << " 后，size = " << s.size()
             << ", capacity = " << s.capacity() << endl;
    }
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