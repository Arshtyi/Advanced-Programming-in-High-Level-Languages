#include <bits/stdc++.h>
using namespace std;
signed main()
{
    stack<string> wordStack;
    string str;
    cin >> str;
    string currentWord;
    for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
    {
        if (*iter == ',')
            wordStack.push(currentWord), currentWord.clear();
        else
            currentWord += *iter;
    }
    if (!currentWord.empty())
        wordStack.push(currentWord);
    while (!wordStack.empty())
        cout << wordStack.top() << endl, wordStack.pop();
    return 0;
}