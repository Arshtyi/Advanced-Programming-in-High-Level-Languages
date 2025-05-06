#include <iostream>
using namespace std;

// 问题9-4：在双向链表中使用的结点类与单链表中使用的结点类相比，应有何不同？
//
// 回答：双向链表中的结点类与单链表中的结点类相比，主要区别在于多了一个指向前驱结点的指针。
// 单链表结点类只包含数据域和指向下一个结点的指针，而双向链表结点类除此之外还需要一个指向前一个结点的指针。
// 这使得双向链表可以双向遍历，既能向后访问也能向前访问，便于实现一些单链表难以高效完成的操作，
// 如在O(1)时间内删除给定结点等。

// 实现双向链表中使用的结点类DNode
template <class T>
class DNode
{
public:
    T data;          // 数据域
    DNode<T> *prior; // 指向前驱结点的指针
    DNode<T> *next;  // 指向后继结点的指针

    // 构造函数
    DNode() : prior(nullptr), next(nullptr) {}
    DNode(T d, DNode<T> *p = nullptr, DNode<T> *n = nullptr) : data(d), prior(p), next(n) {}
};

// 测试代码
int main()
{
    // 创建一个简单的双向链表 1 <-> 2 <-> 3
    DNode<int> *head = new DNode<int>(1);
    DNode<int> *node2 = new DNode<int>(2);
    DNode<int> *node3 = new DNode<int>(3);

    // 连接结点
    head->next = node2;
    node2->prior = head;
    node2->next = node3;
    node3->prior = node2;

    // 遍历并输出
    cout << "正向遍历双向链表：";
    DNode<int> *current = head;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    cout << "反向遍历双向链表：";
    current = node3;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->prior;
    }
    cout << endl;

    // 释放内存
    delete head;
    delete node2;
    delete node3;

    return 0;
}