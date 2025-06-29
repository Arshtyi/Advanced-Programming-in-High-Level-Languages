#include <iostream>
using namespace std;
class Object
{
    int _id;

public:
    Object(int id) : _id(id)
    {
        if (_id < 0)
            throw "invalid argument";
        cout << "C" << _id << endl;
    }
    ~Object()
    {
        cout << "D" << _id << endl;
    }
};
int main()
{
    try
    {
        Object a(1), b(-1), c(2);
    }
    catch (const char *err)
    {
        cout << err << endl;
    }
    return 0;
}