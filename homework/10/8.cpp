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
class RandomNumberGenerator
{
private:
    mt19937 gen;
    uniform_int_distribution<int> dist;

public:
    RandomNumberGenerator(int min_val, int max_val) : dist(min_val, max_val)
    {
        random_device rd;
        gen = mt19937(rd());
    }
    int operator()()
    {
        return dist(gen);
    }
};

void solve()
{
    int n;
    cin >> n;
    RandomNumberGenerator rng(0, 9);
    vector<int> container(n);
    generate(container.begin(), container.end(), rng);
    for (int i = 0; i < n; ++i)
        cout << container[i] << " ";
    cout << endl;
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