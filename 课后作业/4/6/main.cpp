#include <iostream>

class Dog
{
public:
    int age;
    double weight;

    // 普通构造函数
    Dog(int age, double weight) : age(age), weight(weight) {}

    // 复制构造函数
    Dog(const Dog &other) : age(other.age), weight(other.weight)
    {
        std::cout << "Copy constructor called" << std::endl;
    }

    // 赋值运算符
    Dog &operator=(const Dog &other)
    {
        if (this != &other)
        {
            age = other.age;
            weight = other.weight;
            std::cout << "Assignment operator called" << std::endl;
        }
        return *this;
    }

    // 显示狗的信息
    void display() const
    {
        std::cout << "Dog age: " << age << ", weight: " << weight << std::endl;
    }
};

int main()
{
    Dog dog1(5, 20.5);
    Dog dog2(dog1); // 调用复制构造函数

    dog1.display();
    dog2.display();

    Dog dog3(3, 15.0);
    dog3 = dog1; // 调用赋值运算符

    dog3.display();

    return 0;
}