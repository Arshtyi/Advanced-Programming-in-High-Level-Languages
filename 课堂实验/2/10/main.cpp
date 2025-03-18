#include <iostream>

using namespace std;

struct People
{

    unsigned food;
};

// 在这里实现eat和how_are_you两个函数

void eat(People &p, int amount)
{
    p.food += amount;
}

void how_are_you(const People &p)
{
    cout << p.food << "\n";
    if (p.food == 0)
    {
        cout << "I am starved" << endl;
    }
    else if (p.food < 5)
    {
        cout << "I am hungry" << endl;
    }
    else
    {
        cout << "I am fine, thank you and you?" << endl;
    }
}

int main()
{
    struct People p = {0};

    eat(p, 3);

    p.food -= 10;

    how_are_you(p);
}