#include <iostream>

class Student
{
private:
    int stid;
    static int numOfStudents;

public:
    // 构造函数
    // Constructor
    Student(int id) : stid(id)
    {
        numOfStudents++;
    }

    // 析构函数
    // Destructor
    ~Student()
    {
        numOfStudents--;
        std::cout << "学号: " << stid << ", 学生总数: " << numOfStudents << std::endl;
    }

    // 打印学生信息
    // Print student information
    void print()
    {
        std::cout << "Student ID: " << stid << ", Total students: " << numOfStudents << std::endl;
    }
    void printAddr()
    {

        std::cout << &stid << " " << &numOfStudents << std::endl;
    }
    // 打印并返回学生总数
    // Print and return the total number of students
    static int printNumOfStudents()
    {
        std::cout << "当前学生总数: " << numOfStudents << std::endl;
        return numOfStudents;
    }
};

// Initialize static member
int Student::numOfStudents = 0;

int main()
{
    Student::printNumOfStudents();

    Student s1(0);
    Student s2(1);
    s1.printAddr(), s2.printAddr();
    {
        Student s3(2);
        Student::printNumOfStudents();
    }

    Student::printNumOfStudents();
    s1.printNumOfStudents();

    return 0;
}