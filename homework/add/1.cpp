#include <iostream>
using namespace std;
class Count
{
    int *_count;

public:
    Count() : _count(new int(1)) {}
    Count(const Count &r) : _count(r._count) { ++*_count; }
    ~Count()
    {
        if (--*_count == 0)
            delete _count;
    }
    operator int() const
    {
        return *_count;
    }
};

int main()
{
    Count a, b, c(a), &d(b);
    {
        Count *p = new Count(c);
    }
    cout << a << endl
         << b << endl
         << c << endl
         << d << endl;
    return 0;
}