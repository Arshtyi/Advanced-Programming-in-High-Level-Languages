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
    stack<int> stk;
    queue<int> que;
    priority_queue<int> pq;
    stk.push(5);
    stk.push(1);
    stk.push(4);
    stk.push(6);
    que.push(5);
    que.push(1);
    que.push(4);
    que.push(6);
    pq.push(5);
    pq.push(1);
    pq.push(4);
    pq.push(6);
    cout << "stack: " << stk.top() << endl;
    stk.pop();
    cout << "queue: " << que.front() << endl;
    que.pop();
    cout << "priority_queue: " << pq.top() << endl;
    pq.pop();
    cout << "stack: " << stk.top() << endl;
    stk.pop();
    cout << "queue: " << que.front() << endl;
    que.pop();
    cout << "priority_queue: " << pq.top() << endl;
    pq.pop();
    stk.push(2);
    stk.push(3);
    que.push(2);
    que.push(3);
    pq.push(2);
    pq.push(3);
    cout << "stack: " << stk.top() << endl;
    stk.pop();
    cout << "queue: " << que.front() << endl;
    que.pop();
    cout << "priority_queue: " << pq.top() << endl;
    pq.pop();
    cout << "stack: " << stk.top() << endl;
    stk.pop();
    cout << "queue: " << que.front() << endl;
    que.pop();
    cout << "priority_queue: " << pq.top() << endl;
    pq.pop();
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