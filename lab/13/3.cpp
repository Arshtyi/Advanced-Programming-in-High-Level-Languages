#include <iostream>
#include <fstream>
#include <string>

class Dog
{
private:
    double weight;
    int age;

public:
    Dog(double w = 0, int a = 0) : weight(w), age(a) {}
    void setWeight(double w) { weight = w; }
    void setAge(int a) { age = a; }
    double getWeight() const { return weight; }
    int getAge() const { return age; }
    void printInfo() const
    {
        std::cout << "狗的体重: " << weight << " kg, 年龄: " << age << " 岁" << std::endl;
    }
};

int main()
{
    std::cout << "===== 文本方式操作文件 =====" << std::endl;
    Dog dog1(5, 10);
    std::cout << "dog1：";
    dog1.printInfo();
    std::ofstream outTextFile("dog_text.txt");
    if (outTextFile.is_open())
    {
        outTextFile << dog1.getWeight() << std::endl;
        outTextFile << dog1.getAge() << std::endl;
        outTextFile.close();
        std::cout << "已将dog1信息以文本方式写入文件dog_text.txt" << std::endl;
    }
    else
    {
        std::cerr << "无法打开文件进行写入" << std::endl;
        return 1;
    }
    Dog dog2;
    std::ifstream inTextFile("dog_text.txt");
    if (inTextFile.is_open())
    {
        double weight;
        int age;
        inTextFile >> weight >> age;
        dog2.setWeight(weight);
        dog2.setAge(age);
        inTextFile.close();
        std::cout << "dog2从文本文件读取的信息：";
        dog2.printInfo();
    }
    else
    {
        std::cerr << "无法打开文件进行读取" << std::endl;
        return 1;
    }
    std::cout << "\n===== 二进制方式操作文件 =====" << std::endl;
    dog1.setWeight(5);
    dog1.setAge(10);
    std::cout << "dog1的信息：";
    dog1.printInfo();
    std::ofstream outBinaryFile("dog_binary.dat", std::ios::binary);
    if (outBinaryFile.is_open())
    {
        outBinaryFile.write(reinterpret_cast<char *>(&dog1), sizeof(Dog));
        outBinaryFile.close();
        std::cout << "已将dog1信息以二进制方式写入文件dog_binary.dat" << std::endl;
    }
    else
    {
        std::cerr << "无法打开文件进行写入" << std::endl;
        return 1;
    }
    Dog dog2Binary;
    std::ifstream inBinaryFile("dog_binary.dat", std::ios::binary);
    if (inBinaryFile.is_open())
    {
        inBinaryFile.read(reinterpret_cast<char *>(&dog2Binary), sizeof(Dog));
        inBinaryFile.close();
        std::cout << "dog2从二进制文件读取的信息：";
        dog2Binary.printInfo();
    }
    else
    {
        std::cerr << "无法打开文件进行读取" << std::endl;
        return 1;
    }

    return 0;
}