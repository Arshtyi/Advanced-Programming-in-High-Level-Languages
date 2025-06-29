#include <iostream>
using namespace std;
class B
{
public:
    B() {}
    B(int i) { b = i; }
    virtual void virfun()
    {
        cout << "B::virfun() called.\n";
    }

private:
    int b;
};
class D : public B
{
public:
    D() {}
    D(int i, int j) : B(i) { d = j; }

private:
    int d;
    void virfun()
    {
        cout << "D::virfun() called.\n";
    }
};
void fun(B *obj)
{
    obj->virfun();
}
int main()
{
    B *pb = new B;
    fun(pb);
    D *pd = new D;
    fun(pd);
    pb = pd;
    fun(pb);
    pd = dynamic_cast<D *>(pb);
    fun(pd);
}