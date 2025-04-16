#include <iostream>
#include <cmath>
using namespace std;

// 抽象类Shape
class Shape
{
public:
    // 纯虚函数计算面积
    virtual double getArea() = 0;
    // 纯虚函数计算周长
    virtual double getPerim() = 0;
    // 虚析构函数
    virtual ~Shape() {}
};

// 派生类Rectangle
class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    // 构造函数
    Rectangle(double l, double w) : length(l), width(w) {}

    // 实现计算面积的函数
    double getArea() override
    {
        return length * width;
    }

    // 实现计算周长的函数
    double getPerim() override
    {
        return 2 * (length + width);
    }
};

// 派生类Circle
class Circle : public Shape
{
private:
    double radius;
    const double PI = 3.14159;

public:
    // 构造函数
    Circle(double r) : radius(r) {}

    // 实现计算面积的函数
    double getArea() override
    {
        return PI * radius * radius;
    }

    // 实现计算周长的函数
    double getPerim() override
    {
        return 2 * PI * radius;
    }
};

// 测试函数
int main()
{
    // 创建Rectangle对象
    Rectangle rect(5.0, 3.0);
    cout << "矩形：" << endl;
    cout << "面积 = " << rect.getArea() << endl;
    cout << "周长 = " << rect.getPerim() << endl;

    // 创建Circle对象
    Circle circle(4.0);
    cout << "圆形：" << endl;
    cout << "面积 = " << circle.getArea() << endl;
    cout << "周长 = " << circle.getPerim() << endl;

    // 使用基类指针
    Shape *shapes[2];
    shapes[0] = &rect;
    shapes[1] = &circle;

    cout << "\n通过基类指针调用：" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "图形" << i + 1 << "：" << endl;
        cout << "面积 = " << shapes[i]->getArea() << endl;
        cout << "周长 = " << shapes[i]->getPerim() << endl;
    }

    return 0;
}