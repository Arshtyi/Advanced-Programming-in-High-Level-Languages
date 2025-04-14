#include <iostream>
#include <string>

class Document
{
public:
    std::string name;

    Document(const std::string &name) : name(name) {}
};

class Book : public Document
{
public:
    int pageCount;

    Book(const std::string &name, int pageCount) : Document(name), pageCount(pageCount) {}
};

int main()
{
    Book myBook("C++ Programming", 350);
    std::cout << "Book Name: " << myBook.name << std::endl;
    std::cout << "Page Count: " << myBook.pageCount << std::endl;
    return 0;
}