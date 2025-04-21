#include <iostream>

using namespace std;

class A
{
private:
    const int i = 10;

public:
    void show()
    {
        cout << i << endl;
    }

    friend void modifyUsingFriend(A &obj);
};

void modifyUsingFriend(A &obj)
{
    int &non_const_i = const_cast<int &>(obj.i);
    non_const_i = 20;
}

int main()
{
    A a;

    // modifyUsingFriend(a);

    *reinterpret_cast<int *>(&a) = 20;

    a.show();
}
