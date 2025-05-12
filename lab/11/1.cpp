#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T data;

public:
    Node *next;
    Node();
    Node(const T &data, Node<T> *nt = 0);
    T &getData();
};

template <class T>
Node<T>::Node()
{
    data = 0;
    next = NULL;
}

template <class T>
Node<T>::Node(const T &d, Node<T> *nt)
{
    data = d;
    next = nt;
}

template <class T>
T &Node<T>::getData()
{
    return data;
}

template <class T>
class LinkedList
{
private:
    Node<T> *front, *rear; // 表头和表尾指针
    int size;              // 表中元素个数

public:                                 // 外部接口
    LinkedList();                       // 构造函数
    LinkedList(const LinkedList<T> &L); // 复制构造函数
    ~LinkedList();                      // 析构函数

    int getSize() const;  // 返回链表中元素个数
    bool isEmpty() const; // 链表是否为空
    void clear();         // 清空链表：释放所有节点的内存空间
    void display();

    void insertFront(const T &item);       // 在表头节点front之后插入节点
    void insertRear(const T &item);        // 在链表尾节点rear之前插入节点
    void insertAt(int idx, const T &item); // 在idx位置插入节点

    void deleteFront();     // 删除头节点
    void deleteAt(int idx); // 删除idx位置节点
    T getFront() const;     // 获取队首元素 - 为队列类添加的新方法
};

// 构造函数
template <class T>
LinkedList<T>::LinkedList()
{
    front = new Node<T>(); // 指向新建节点，实际建立一个空的头node结点和尾节点
    rear = new Node<T>();
    front->next = rear;
    size = 0; // 不计算front和rear节点
}

// 析构函数
template <class T>
LinkedList<T>::~LinkedList()
{
    clear();      // 清空释放当前链表
    delete front; // 释放头指针所指节点
    delete rear;  // 释放尾指针所指节点
}

// 返回链表中元素个数
template <class T>
int LinkedList<T>::getSize() const
{
    return size;
}

// 链表是否为空
template <class T>
bool LinkedList<T>::isEmpty() const
{
    return (size == 0);
}

// 清空链表内容：释放所有节点的内存空间
template <class T>
void LinkedList<T>::clear()
{
    Node<T> *temp;
    while (front->next != rear)
    {
        temp = front->next;
        front->next = temp->next;
        delete temp;
    }
    size = 0;
}

template <class T>
void LinkedList<T>::display()
{ // 输出链表
    cout << "List: ";

    Node<T> *temp = front->next;
    while (temp != rear)
    {
        cout << temp->getData() << " ";
        temp = temp->next;
    }

    cout << endl;
}

// 在front节点后插入值
template <class T>
void LinkedList<T>::insertFront(const T &item)
{
    Node<T> *newNode = new Node<T>(item, front->next);
    front->next = newNode;
    size++;
}

// 在链表尾节点之前插入节点
template <class T>
void LinkedList<T>::insertRear(const T &item)
{
    Node<T> *current = front;
    // 找到尾节点的前一个节点
    while (current->next != rear)
    {
        current = current->next;
    }

    Node<T> *newNode = new Node<T>(item, rear);
    current->next = newNode;
    size++;
}

// 在idx位置插入节点
// 如原链表内容为2, 3, 5, 6，insertAt(2,9)之后得到的链表内容为2, 3, 9, 5, 6
template <class T>
void LinkedList<T>::insertAt(int idx, const T &item)
{
    if (idx < 0 || idx > size)
    {
        cout << "Index out of range" << endl;
        return;
    }

    Node<T> *current = front;
    // 找到要插入位置的前一个节点
    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }

    Node<T> *newNode = new Node<T>(item, current->next);
    current->next = newNode;
    size++;
}

// 删除头节点，实质是删除front->next
template <class T>
void LinkedList<T>::deleteFront()
{
    if (isEmpty())
    {
        cout << "List is empty, cannot delete" << endl;
        return;
    }

    Node<T> *temp = front->next;
    front->next = temp->next;
    delete temp;
    size--;
}

// 删除idx位置的节点
// 如原链表内容为2, 3, 5, 6，deleteAt(2)之后得到的链表内容为2, 3, 6
template <class T>
void LinkedList<T>::deleteAt(int idx)
{
    if (idx < 0 || idx >= size)
    {
        cout << "Index out of range" << endl;
        return;
    }

    Node<T> *current = front;
    // 找到要删除位置的前一个节点
    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }

    Node<T> *temp = current->next;
    current->next = temp->next;
    delete temp;
    size--;
}

// 获取队首元素 - 为队列类添加的新方法
template <class T>
T LinkedList<T>::getFront() const
{
    if (isEmpty())
    {
        cout << "List is empty, returning default value" << endl;
        return T();
    }
    return front->next->getData();
}

// 队列类实现
template <class T>
class MyQueue
{
private:
    LinkedList<T> list; // 使用LinkedList作为底层数据结构

public:
    MyQueue() {} // 构造函数

    // 在队尾插入元素
    void push(const T &item)
    {
        list.insertRear(item);
    }

    // 从队首删除元素
    void pop()
    {
        list.deleteFront();
    }

    // 返回队首元素
    T peek()
    {
        return list.getFront();
    }

    // 显示队列中的所有元素
    void display()
    {
        list.display();
    }

    // 判断队列是否为空
    bool isEmpty() const
    {
        return list.isEmpty();
    }

    // 返回队列中元素个数
    int size() const
    {
        return list.getSize();
    }
};

int main()
{
    MyQueue<int> mq;
    for (int i = 0; i < 10; i++)
    {
        mq.push(i);
    }
    mq.pop();
    mq.push(mq.peek());
    mq.pop();
    mq.pop();
    mq.display();
    return 0;
}