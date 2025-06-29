#include <iostream>
using namespace std;
class Object
{
    static int count;

public:
    Object() { count++; }
    Object(const Object &r) { count++; }
    ~Object() { count--; }

    static void print()
    {
        cout << count << endl;
    }
};

int Object::count = 0;

void func()
{
    Object a, b(a);
    Object::print();
    {
        Object c, *p = new Object;
        Object::print();
    }
    Object::print();
}

int main()
{
    Object a;
    a.print();
    func();
    Object::print();
    return 0;
}