#include <iostream>

using namespace std;

class MyArray
{

    int array_size;

    int *arr = NULL;

public:
    MyArray(int asize) : array_size(asize)
    {

        arr = new int[array_size];

        for (int i = 0; i < array_size; i++)
        {

            arr[i] = 0;
        }
    }

    ~MyArray()
    {

        delete arr;
    }
    MyArray &operator=(const MyArray &other)
    {
        if (this == &other)
        { // 自我赋值检查
            return *this;
        }

        if (array_size != other.array_size)
        {
            cout << "Error: Array sizes do not match!" << endl;
            return *this;
        }

        // 执行逐个元素复制
        for (int i = 0; i < array_size; i++)
        {
            arr[i] = other.arr[i];
        }

        return *this;
    }
    int getArraySize() const
    {

        return array_size;
    }

    int getArr(int idx) const
    {

        if (idx >= array_size)
        {

            cout << "overflow" << endl;

            exit(-1);
        }

        return arr[idx];
    }

    void setArr(int idx, int v)
    {

        if (idx >= array_size)
        {

            cout << "overflow" << endl;

            exit(-1);
        }

        arr[idx] = v;
    }

    void print() const
    {

        cout << "addr: " << arr << " ";

        cout << "contents: " << " ";

        for (int i = 0; i < array_size; i++)
        {

            cout << arr[i] << " ";
        }

        cout << endl;
    }
};

int main()
{

    MyArray arr1(10), arr2(10);

    for (int i = 0; i < 10; i++)
    {

        arr1.setArr(i, i);

        arr2.setArr(i, 2 * i);
    }

    arr1.print();

    arr2.print();

    arr1 = arr2;

    arr1.print();
}