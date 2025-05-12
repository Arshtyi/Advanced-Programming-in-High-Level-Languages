#include <iostream>
#include <cassert>
using namespace std;
#define sz 100

// 通用模板声明（前向声明）
template <typename T, int SIZE>
class Stack;

// bool类型的特化版本
template <int SIZE>
class Stack<bool, SIZE>
{ // bool固定
private:
    enum
    {
        UNIT_BITS = sizeof(unsigned) * 8,
        ARRAY_SIZE = (SIZE - 1) / UNIT_BITS + 1
    };
    unsigned list[ARRAY_SIZE];
    int top;

public:
    Stack();
    void push(bool item);
    bool pop();
    void clear();
    bool peek() const;
    bool isEmpty() const;
    bool isFull() const;
};

template <int SIZE>
Stack<bool, SIZE>::Stack() : top(-1)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        list[i] = 0;
    }
}

template <int SIZE>
void Stack<bool, SIZE>::push(bool item)
{
    assert(!isFull());
    int index = ++top / UNIT_BITS;
    list[index] = (list[index] << 1) | (item ? 1 : 0);
}

template <int SIZE>
bool Stack<bool, SIZE>::pop()
{
    assert(!isEmpty());
    int index = top-- / UNIT_BITS;
    bool result = ((list[index] & 1) == 1);
    list[index] >>= 1;
    return result;
}

template <int SIZE>
void Stack<bool, SIZE>::clear()
{
    top = -1;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        list[i] = 0;
    }
}

template <int SIZE>
bool Stack<bool, SIZE>::peek() const
{
    assert(!isEmpty());
    int index = top / UNIT_BITS;
    return ((list[index] & 1) == 1);
}

template <int SIZE>
bool Stack<bool, SIZE>::isEmpty() const
{
    return top == -1;
}

template <int SIZE>
bool Stack<bool, SIZE>::isFull() const
{
    return top == SIZE - 1;
}

int main()
{
    Stack<bool, sz> stk;
    cout << "size of Stack<bool, 100>: " << sizeof(stk) << endl;
    for (int i = 0; i < sz; i++)
    {
        stk.push((bool)(i % 2));
    }
    for (int i = 0; i < sz; i++)
    {
        cout << i << "\t" << stk.pop() << endl;
    }
    return 0;
}