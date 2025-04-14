using namespace std;
#include <iostream>
int main()
{

    int a = 1, b = 1;

    cout << "a = " << a << " b = " << b << endl;

    {

        int b = 3;

        cout << "a = " << a << " b = " << b << endl;
    }

    return 0;
}