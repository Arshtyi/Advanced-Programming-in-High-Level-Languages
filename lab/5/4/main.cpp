#include <iostream>

using namespace std;

class R
{

public:
    R(int r1, int r2) : r1(r1), r2(r2) {}

    void print();

    void print() const;

    void change(int x1, int x2);

private:
    int r1, r2;
};
void R::change(int x1, int x2)
{

    r1 = x1;

    r2 = x2;
}
void R::print()
{

    cout << r1 << ":" << r2 << endl;
}

void R::print() const
{

    cout << r1 << ";" << r2 << endl;
}

int main()
{

    R a(5, 4);

    a.print();

    const R b(20, 52);

    b.print();

    return 0;
}