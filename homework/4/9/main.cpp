#include <iostream>

class Tree
{
private:
    int ages;

public:
    Tree() : ages(0) {}

    void grow(int years)
    {
        ages += years;
    }

    int age() const
    {
        return ages;
    }
};

int main()
{
    Tree tree;
    tree.grow(5);
    std::cout << "Tree age: " << tree.age() << std::endl;
    return 0;
}