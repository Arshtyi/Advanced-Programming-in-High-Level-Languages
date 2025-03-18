#include <iostream>

class Test
{
private:
    static int privateStaticVar;

public:
    static void setPrivateStaticVar(int value)
    {
        privateStaticVar = value;
    }

    static int getPrivateStaticVar()
    {
        return privateStaticVar;
    }
};
int Test::privateStaticVar = 0;

int main()
{
    std::cout << "初始值: " << Test::getPrivateStaticVar() << std::endl;
    Test::setPrivateStaticVar(42);
    std::cout << "更新值: " << Test::getPrivateStaticVar() << std::endl;
    return 0;
}