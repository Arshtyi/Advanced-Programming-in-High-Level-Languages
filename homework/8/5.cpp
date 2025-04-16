#include <iostream>
using namespace std;

class Mammal
{
public:
    virtual void speak()
    {
        cout << "Mammal makes a sound." << endl;
    }
    virtual ~Mammal() {}
};

class Dog : public Mammal
{
public:
    void speak() override
    {
        cout << "Dog barks." << endl;
    }
};

int main()
{
    Dog dog;
    dog.speak(); // 调用 Dog 类的 speak 方法

    return 0;
}