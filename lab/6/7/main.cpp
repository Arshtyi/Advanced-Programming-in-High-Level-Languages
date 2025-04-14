#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);
    std::string str1 = "you type in: " + str;
    std::cout << str1 << std::endl;
    return 0;
}