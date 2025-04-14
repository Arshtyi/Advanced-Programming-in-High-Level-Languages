// 运行并分析结果，解释析构函数的调用顺序

// 析构函数示例

#include <iostream>

#include <string>

using namespace std;

class Student

{
public:
    Student(int n, string nam, char s)

    {
        num = n;

        name = nam;

        sex = s;

        cout << "Constructor called." << endl;
    }

    ~Student()

    {
        cout << name << ":Destructor called." << endl;
    }

    void display()

    {
        cout << "num:" << num << endl;

        cout << "name:" << name << endl;

        cout << "sex:" << sex << endl
             << endl;
    }

private:
    int num;

    string name;

    char sex;
};

int main()

{
    Student stud1(10010, "Wang_li", 'f');

    stud1.display();

    Student stud2(10011, "Zhang_fun", 'm');

    stud2.display();

    return 0;
}