#include <stdio.h>

struct Student
{ // 学生信息结构体

    int num; // 学号

    const char *name; // 姓名，字符串对象，将在第6章详细介绍

    char sex; // 性别
    int age;
    // 年龄

    Student(int n, const char *nm, char s, int a) : num(n), name(nm), sex(s), age(a) {}

private:
    float gpa;   // 平均绩点
    int credits; // 学分
public:
    void setGPA(float g) { gpa = g; }
    float getGPA() const { return gpa; }
    void setCredits(int c) { credits = c; }
    int getCredits() const { return credits; }
};

int main()
{

    Student stu = {97001, "Lin Lin", 'F', 19};

    printf("Num:  %d\n", stu.num);

    printf("Num:  %s\n", stu.name);

    printf("Num:  %c\n", stu.sex);

    printf("Num:  %d\n", stu.age);

    return 0;
}