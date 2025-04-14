#include <iostream>

class Rectangle
{
private:
    class Point
    {
    public:
        double x, y;

        Point(double x = 0, double y = 0) : x(x), y(y) {}
    };

    Point topLeft;
    Point bottomRight;

public:
    Rectangle(double tlx, double tly, double brx, double bry)
        : topLeft(tlx, tly), bottomRight(brx, bry) {}

    double area() const
    {
        double width = bottomRight.x - topLeft.x;
        double height = topLeft.y - bottomRight.y;
        return width * height;
    }

    void display() const
    {
        std::cout << "左上角: (" << topLeft.x << ", " << topLeft.y << "), "
                  << "右下角: (" << bottomRight.x << ", " << bottomRight.y << ")" << std::endl;
    }
};

int main()
{
    Rectangle rect(0.0, 10.0, 10.0, 0.0);

    rect.display();
    std::cout << "面积: " << rect.area() << std::endl;

    return 0;
}
