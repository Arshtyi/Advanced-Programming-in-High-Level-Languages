#include <iostream>
#include <memory>
using namespace std;

class A
{
    int id;

public:
    A(int i) : id(i)
    {
        cout << "object " << id << " is constructed" << endl;
    }
    ~A()
    {
        cout << "object " << id << " is deconstructed" << endl;
    }
};
int main()
{
    A *a1 = new A(1);
    A a2(2);
    A *a3 = new A(3);
    auto_ptr<A> a3_ptr(a3);
    delete a1;
}