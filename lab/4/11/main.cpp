#include <iostream>

enum Core
{
    Single,
    Dual,
    Quad
};
enum Words
{
    Bit32,
    Bit64
};
enum HyperThread
{
    Support,
    NotSupport
};
class CPU
{
public:
    CPU(unsigned frequency, Core type, Words length, HyperThread mode) : frequence(frequency), CoreType(type), WordLen(length), mode(mode) {}
    void show();

private:
    unsigned frequence : 16; // Changed from 32 to 16 bits
    Core CoreType : 2;       // Changed from 3 to 2 bits
    Words WordLen : 1;       // Changed from 2 to 1 bit
    HyperThread mode : 1;    // Changed from 2 to 1 bit
};
void CPU::show()
{
    std::cout << "Frequency:    " << frequence << "  (MHz)" << std::endl;
    std::cout << "Core:    ";
    switch ((unsigned)CoreType)
    {
    case Single:
        std::cout << "Single-Core" << std::endl;
        break;
    case Dual:

        std::cout << "Dual-Core" << std::endl;
        break;
    case Quad:
        std::cout << "Quad-Core" << std::endl;
        break;
    default:
        std::cout << "Unknown Core Type" << std::endl;
        break;
    }
    std::cout << "Words:    ";
    switch ((unsigned)WordLen)
    {
    case Bit32:
        std::cout << "32-bits len" << std::endl;
        break;
    case Bit64:
        std::cout << "64-bits len" << std::endl;
        break;
    default:
        std::cout << "Unknown Word Length" << std::endl;
        break;
    }
    std::cout << "HyperThread:    ";
    switch ((unsigned)mode)
    {
    case Support:
        std::cout << "Support Hyper-Thread" << std::endl;
        break;
    case NotSupport:
        std::cout << "Not Support Hyper-Thread" << std::endl;
        break;
    default:
        std::cout << "Unknown Hyper-Thread Mode" << std::endl;
        break;
    }
}
int main()
{
    CPU myCPU(3000, Dual, Bit64, Support);
    myCPU.show();
    std::cout << "Size of class CPU: " << sizeof(myCPU) << std::endl;
    return 0;
}