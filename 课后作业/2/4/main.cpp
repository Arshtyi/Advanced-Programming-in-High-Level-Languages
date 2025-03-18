#include <bits/stdc++.h>
using namespace std;
signed main(){
    int a = 30;
    int b = a++;
    int c = ++a;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    for (int i = 0,j = 0; i < 3; ++i) {
        cout << "i = " << i << " j = " << j << endl;
    }

    return 0;
}