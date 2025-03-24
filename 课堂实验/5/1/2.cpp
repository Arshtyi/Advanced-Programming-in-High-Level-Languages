using namespace std;
#include <iostream>
int main()
{

    int *pt;

    {

        int a = 315;

        pt = &a;
    }

    cout << *pt << endl;

    return 0;
}