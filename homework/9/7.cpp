#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ROF(i, a, b) for (int i = (a); i > (b); --i)
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
template <class T>
void insertionSort(T a[], int n)
{
    int i, j;
    T temp;

    cout << "初始数组：";
    FOR(k, 0, n)
    cout << a[k] << " ";
    cout << endl;

    FOR(i, 1, n)
    {
        int j = i;
        T temp = a[i];

        // 在每次插入前输出当前要插入的元素
        cout << "\n第" << i << "次插入: 插入元素 " << temp << endl;

        while (j > 0 && temp < a[j - 1])
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;

        // 在每次插入后输出当前数组状态
        cout << "插入后数组: ";
        FOR(k, 0, n)
        cout << a[k] << " ";
        cout << endl;
    }
}
void solve()
{
    int data1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = sizeof(data1) / sizeof(data1[0]);

    insertionSort(data1, size);

    cout << "\n最终排序结果: ";
    FOR(i, 0, size)
    cout << data1[i] << " ";
    cout << endl;
}
signed main()
{
    LOCAL;
    notie;
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}