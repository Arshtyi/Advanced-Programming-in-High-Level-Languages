#include <iostream>
using namespace std;

class Object
{
protected:
    double weight;

public:
    Object(double w) : weight(w)
    {
        cout << "Object constructor called" << endl;
    }
    ~Object()
    {
        cout << "Object destructor called" << endl;
    }

    void setWeight(double w)
    {
        weight = w;
    }

    double getWeight() const
    {
        return weight;
    }
};

class Box : public Object
{
private:
    double height;
    double width;

public:
    Box(double w, double h, double wd) : Object(w), height(h), width(wd)
    {
        cout << "Box constructor called" << endl;
    }

    ~Box()
    {
        cout << "Box destructor called" << endl;
    }
    void setHeight(double h)
    {
        height = h;
    }
    double getHeight() const
    {
        return height;
    }

    void setWidth(double wd)
    {
        width = wd;
    }

    double getWidth() const
    {
        return width;
    }
};

int main()
{
    Box box(10.5, 20.0, 15.0);
    cout << "Weight: " << box.getWeight() << endl;
    cout << "Height: " << box.getHeight() << endl;
    cout << "Width: " << box.getWidth() << endl;

    box.setWeight(12.0);
    box.setHeight(25.0);
    box.setWidth(18.0);

    cout << "Updated Weight: " << box.getWeight() << endl;
    cout << "Updated Height: " << box.getHeight() << endl;
    cout << "Updated Width: " << box.getWidth() << endl;

    return 0;
}