#include <iostream>
#include <cmath>

class Circle
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const
    {
        return M_PI * radius * radius;
    }

    void display() const
    {
        std::cout << "半径: " << radius << std::endl;
    }
};

int main()
{
    Circle circle(5.0);

    circle.display();
    std::cout << "面积: " << circle.getArea() << std::endl;

    return 0;
}