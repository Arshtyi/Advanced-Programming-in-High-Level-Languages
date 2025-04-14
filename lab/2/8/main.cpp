#include <iostream>

using namespace std;

int main()
{

    int n = 0;

    for (;;)
    {

        cout << n << " ";
        if (n == 9)
            break;
        n++;
    }

    cout << endl;

    return 0;
}