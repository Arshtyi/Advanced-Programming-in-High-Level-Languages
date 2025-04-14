#include <iostream>
#include <string>

class Address
{
public:
    std::string city;
    std::string street;
    int number;

    Address(const std::string &city = "", const std::string &street = "", int number = 0)
        : city(city), street(street), number(number) {}

    void display() const
    {
        std::cout << "地址: " << city << ", " << street << ", " << number << std::endl;
    }
};

class People
{
private:
    std::string name;
    int age;
    Address address;

public:
    // 构造函数
    People(const std::string &name = "", int age = 0, const Address &address = Address())
        : name(name), age(age), address(address) {}

    // 复制构造函数
    People(const People &other)
        : name(other.name), age(other.age), address(other.address) {}

    // 析构函数
    ~People() {}

    // 内联成员函数
    inline void setName(const std::string &name)
    {
        this->name = name;
    }

    // 带默认形参值的成员函数
    void setAge(int age = 18)
    {
        this->age = age;
    }

    void display() const
    {
        std::cout << "姓名: " << name << ", 年龄: " << age << std::endl;
        address.display();
    }
};

int main()
{
    Address addr("北京", "四环", 10);
    People person("张三", 30, addr);
    person.display();

    People person2(person); // 使用复制构造函数
    person2.setName("李四");
    person2.setAge();
    person2.display();

    return 0;
}