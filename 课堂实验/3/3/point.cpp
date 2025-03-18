#include <iostream>

#include "point.h"

using namespace std;

// 形参为Point类对象的函数

void fun1(Point p)
{

    cout << p.getX() << endl;
}

// 返回值为Point类对象的函数

Point fun2()
{

    Point a(1, 2);

    return a;
}

Point::Point(const Point &p)
{

    x = p.x;

    y = p.y;

    cout << "Calling the copy constructor " << endl;
}
