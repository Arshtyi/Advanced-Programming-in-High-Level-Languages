#include <iostream>
using namespace std;
class Object
{
    int _id;

public:
    Object(int id = 0) : _id(id)
    {
        cout << "C " << _id << endl;
    }
    Object(const Object &r) : _id(r._id)
    {
        cout << "M " << _id << endl;
    }
    ~Object()
    {
        cout << "D " << _id << endl;
    }
};

Object *func(Object &a, Object b)
{
    static Object s = a;
    return &s;
}

int main()
{
    Object a(1), b;
    Object &c(*func(a, b));
    return 0;
}