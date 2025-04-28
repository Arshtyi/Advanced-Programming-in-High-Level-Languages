#include <bits/stdc++.h>
using namespace std;

template <class T>
class Store
{ // 类模板：实现对任意类型数据进行存取
private:
    T item;         // item用于存放任意类型的数据
    bool haveValue; // haveValue标记item是否已被存入内容
public:
    Store();                  // 缺省形式（无形参）的构造函数
    T &getElem();             // 提取数据函数
    void putElem(const T &x); // 存入数据函数
};
template <class T> // 默认构造函数的实现
Store<T>::Store() : haveValue(false)
{
}
template <class T> // 提取数据函数的实现
T &Store<T>::getElem()
{
    // 如试图提取未初始化的数据，则终止程序
    if (!haveValue)
    {
        cout << "No item present!" << endl;
        exit(1); // 使程序完全退出，返回到操作系统。
    }
    return item; // 返回item中存放的数据
}
template <class T> // 存入数据函数的实现
void Store<T>::putElem(const T &x)
{
    // 将haveValue 置为true，表示item中已存入数值
    haveValue = true;
    item = x; // 将x值存入item
}
signed main()
{
    // Define a Store that can hold another Store containing an int
    Store<Store<int>> a;

    // Create a Store<int> to hold our integer
    Store<int> intStore;
    intStore.putElem(10);

    // Store the intStore in our outer Store
    a.putElem(intStore);

    // Retrieve and print the value (10)
    cout << a.getElem().getElem() << endl;
    return 0;
}