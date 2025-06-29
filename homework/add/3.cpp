#include <iostream>
using namespace std;
struct A
{
    A(int id) { cout << "A " << id << endl; }
};
struct B
{
    B(int id) { cout << "B " << id << endl; }
};
struct D
    : public B,
      virtual public A
{
    B b;
    A a;
    D()
        : a(1), b(1), B(2), A(2) {}
};
int main()
{
    D d;
    return 0;
}