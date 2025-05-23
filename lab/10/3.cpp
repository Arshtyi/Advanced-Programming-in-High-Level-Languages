#include <iostream>
#include <cassert>
using namespace std;

template <class T> // 数组类模板定义
class Array
{
private:
    T *list;  // 用于存放动态分配的数组内存首地址
    int size; // 数组大小（元素个数）
public:
    Array(int sz = 50);                       // 构造函数
    Array(const Array<T> &a);                 // 拷贝构造函数
    ~Array();                                 // 析构函数
    Array<T> &operator=(const Array<T> &rhs); // 重载"="
    T &operator[](int i);                     // 重载"[]”
    const T &operator[](int i) const;
    operator T(); // 重载到T类型的转换
    operator const T() const;
    int getSize() const; // 取数组的大小
    void resize(int sz); // 修改数组的大小
};
template <class T>
Array<T>::Array(int sz)
{                       // 构造函数
    assert(sz >= 0);    // sz为数组大小（元素个数），应当非负
    size = sz;          // 将元素个数赋值给变量size
    list = new T[size]; // 动态分配size个T类型的元素空间
}
template <class T>
Array<T>::~Array()
{ // 析构函数
    delete[] list;
}
template <class T>
Array<T>::Array(const Array<T> &a)
{                  // 拷贝构造函数
    size = a.size; // 从对象x取得数组大小，并赋值给当前对象的成员
    // 为对象申请内存并进行出错检查
    list = new T[size];            // 动态分配n个T类型的元素空间
    for (int i = 0; i < size; i++) // 从对象X复制数组元素到本对象
        list[i] = a.list[i];
}
// 重载"="运算符，将对象rhs赋值给本对象。实现对象之间的整体赋值
template <class T>
Array<T> &Array<T>::operator=(const Array<T> &rhs)
{
    if (&rhs != this)
    {
        // 如果本对象中数组大小与rhs不同，则删除数组原有内存，然后重新分配
        if (size != rhs.size)
        {
            delete[] list;      // 删除数组原有内存
            size = rhs.size;    // 设置本对象的数组大小
            list = new T[size]; // 重新分配n个元素的内存
        }
        // 从对象X复制数组元素到本对象
        for (int i = 0; i < size; i++)
            list[i] = rhs.list[i];
    }
    return this; // 返回当前对象的引用
}
// 重载下标运算符，实现与普通数组一样通过下标访问元素，并且具有越界检查功能
template <class T>
T &Array<T>::operator[](int n)
{
    if (n == size)
    {
        resize(size * 2); // 将容量扩展为当前大小的两倍
    }
    assert(n >= 0 && n < size); // 检查下标是否越界
    return list[n];             // 返回下标为n的数组元素
}
template <class T>
const T &Array<T>::operator[](int n) const
{
    assert(n >= 0 && n < size); // 检查下标是否越界
    return list[n];             // 返回下标为n的数组元素
}
// 重载指针转换运算符，将Array类的对象转换为T类型的指针
template <class T>
Array<T>::operator T()
{                // 转换为T类型的指针T的类型转换函数
    return list; // 返回当前对象中私有数组的首地址
}
template <class T>
Array<T>::operator const T() const
{
    return list; // 返回当前对象中私有数组的首地址
}
// 取当前数组的大小
template <class T>
int Array<T>::getSize() const
{
    return size;
}
// 将数组大小修改为sz
template <class T>
void Array<T>::resize(int sz)
{
    assert(sz >= 0); // 检查sz是否非负
    if (sz == size)  // 如果指定的大小与原有大小一样，什么也不做
        return;
    T *newList = new T[sz];          // 申请新的数组内存
    int n = (sz < size) ? sz : size; // 将sz与size中较小的一个赋值给n
    // 将原有数组中前n个元素复制到新数组中
    for (int i = 0; i < n; i++)
        newList[i] = list[i];
    delete[] list;  // 删除原数组
    list = newList; // 使list指向新数组
    size = sz;      // 更新size
}

int main()
{
    Array<int> a(5);
    for (int i = 0; i < 10; i++)
    {
        a[i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << i << "\t" << a[i] << endl;
    }
    return 0;
}
