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
void solve_using_multiset()
{
    cout << "使用 multiset 实现：" << endl;
    string word;
    multiset<string> words;
    cout << "请输入单词(输入'exit'结束)：" << endl;
    while (cin >> word && word != "exit")
    {
        auto count = words.count(word);
        if (count > 0)
            cout << "单词 '" << word << "' 已出现过，出现次数: " << count << endl;
        else
            cout << "单词 '" << word << "' 首次出现" << endl;
        words.insert(word);
    }
}
void solve_using_map()
{
    cout << "\n使用 map 实现：" << endl;
    string word;
    map<string, int> words;
    cout << "请输入单词(输入'exit'结束)：" << endl;
    while (cin >> word && word != "exit")
    {
        if (words.find(word) != words.end())
            cout << "单词 '" << word << "' 已出现过，出现次数: " << words[word] << endl;
        else
            cout << "单词 '" << word << "' 首次出现" << endl;
        words[word]++;
    }
}

void solve()
{
    cout << "请选择实现方式（1: multiset, 2: map, 3: 两种方式都使用）：" << endl;
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice)
    {
    case 1:
        solve_using_multiset();
        break;
    case 2:
        solve_using_map();
        break;
    case 3:
        solve_using_multiset();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        solve_using_map();
        break;
    default:
        cout << "无效的选择！" << endl;
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