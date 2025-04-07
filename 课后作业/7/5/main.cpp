#include <iostream>
#include <cmath>
using namespace std;

// 基类 Shape
class Shape
{
public:
    virtual double getArea() const = 0;
    virtual ~Shape() {}
};

// 派生类 Rectangle
class Rectangle : public Shape
{
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override
    {
        return width * height;
    }
};

// 派生类 Circle
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double getArea() const override
    {
        return M_PI * radius * radius;
    }
};

// 派生类 Square
class Square : public Rectangle
{
public:
    Square(double side) : Rectangle(side, side) {}
};

int main()
{
    Shape *shapes[3];

    shapes[0] = new Rectangle(3.0, 4.0);
    shapes[1] = new Circle(5.0);
    shapes[2] = new Square(2.5);

    for (int i = 0; i < 3; ++i)
    {
        cout << "Shape " << i + 1 << " Area: " << shapes[i]->getArea() << endl;
        delete shapes[i];
    }

    return 0;
}