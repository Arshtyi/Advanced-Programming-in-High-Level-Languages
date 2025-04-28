#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

template <class T, int SIZE = 50>
class Stack
{
private:
    T list[SIZE];
    int top;

public:
    Stack();
    void push(const T &item);
    T pop();
    void clear();
    const T &peek() const;
    bool isEmpty() const;
    bool isFull() const;
};
// 模板的实现
template <class T, int SIZE>
Stack<T, SIZE>::Stack() : top(-1) {}
template <class T, int SIZE>
void Stack<T, SIZE>::push(const T &item)
{
    assert(!isFull());
    list[++top] = item;
}
template <class T, int SIZE>
T Stack<T, SIZE>::pop()
{
    assert(!isEmpty());
    return list[top--];
}
template <class T, int SIZE>
const T &Stack<T, SIZE>::peek() const
{
    assert(!isEmpty());
    return list[top]; // 返回栈顶元素
}
template <class T, int SIZE>
bool Stack<T, SIZE>::isEmpty() const
{
    return top == -1;
}
template <class T, int SIZE>
bool Stack<T, SIZE>::isFull() const
{
    return top == SIZE - 1;
}
template <class T, int SIZE>
void Stack<T, SIZE>::clear()
{
    top = -1;
}

class Calculator
{ // 计算器类
private:
    Stack<double> s; // 操作数栈
    Stack<char> sc;
    void enter(double num); // 将操作数num压入栈
    void enter(char ch);    // 将操作符ch压入栈

    // 连续将两个操作数弹出栈，放在opnd1和opnd2中
    bool getTwoOperands(double &opnd1, double &opnd2);

    void compute(char op); // 执行由操作符op指定的运算
public:
    void run();   // 运行计算器程序
    void clear(); // 清空操作数栈
};

inline double stringToDouble(const string &str)
{
    istringstream stream(str); // 字符串输入流
    double result;
    stream >> result;
    return result;
}

void Calculator::enter(double num)
{ // 将操作数num压入栈
    s.push(num);
}

void Calculator::enter(char ch)
{ // 将操作数num压入栈
    sc.push(ch);
}

bool Calculator::getTwoOperands(double &opnd1, double &opnd2)
{
    if (s.isEmpty())
    { // 检查栈是否空
        cerr << "Missing right operand!" << endl;
        return false;
    }
    opnd1 = s.pop(); // 将右操作数弹出栈

    if (s.isEmpty())
    { // 检查栈是否空
        cerr << "Missing left operand!" << endl;
        return false;
    }
    opnd2 = s.pop(); // 将左操作数弹出栈

    return true;
}

void Calculator::compute(char op)
{ // 执行运算
    double operand1, operand2;
    bool result = getTwoOperands(operand1, operand2);
    if (result)
    { // 如果成功，执行运算并将运算结果压入栈
        switch (op)
        {
        case '+':
            s.push(operand2 + operand1);
            break;
        case '-':
            s.push(operand2 - operand1);
            break;
        default:
            cerr << "Unrecognized operator!" << endl;
            break;
        }
    }
    else
        s.clear(); // 操作数不够，清空栈
}

void Calculator::run()
{ // 读入并处理后缀表达式
    string str;
    while (cin >> str, str != "q")
    {
        switch (str[0])
        {
        case '-':
        case '+': // 遇到操作符时
            enter(str[0]);
            break;
        default: // 若读入的是操作数，转换为整型后压入栈
            enter(stringToDouble(str));
            break;
        }
    }
    while (!sc.isEmpty())
    {
        compute(sc.peek());
        sc.pop();
    }
    cout << "= " << s.peek() << " "; // 输出本次运算结果
}
void Calculator::clear()
{ // 清空操作数栈
    s.clear();
}
int main()
{
    Calculator c;
    c.run();
    return 0;
}