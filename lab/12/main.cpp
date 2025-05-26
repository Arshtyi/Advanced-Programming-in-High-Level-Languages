#include <iostream>
#include <iomanip>
#include "Polyhedron.hpp"
template <typename T>
void calPolyhedron(const char *filename)
{
    try
    {
        // std::cout << "正在读取文件: " << filename << std::endl;
        Polyhedron<T> poly(filename);
        // std::cout << "顶点数量: " << poly.getVertexCount() << std::endl;
        // std::cout << "面片数量: " << poly.getFacetCount() << std::endl;
        Point<T> low = poly.get_low();
        Point<T> high = poly.get_high();
        std::cout << std::setprecision(6); // 设置为6位有效数字
        // std::cout << "包围盒下界: ("
        //   << low.getX() << ", "
        //   << low.getY() << ", "
        //   << low.getZ() << ")" << std::endl;

        // std::cout << "包围盒上界: ("
        //   << high.getX() << ", "
        //   << high.getY() << ", "
        //   << high.getZ() << ")" << std::endl;
        std::cout << "多面体表面积: " << poly.area() << std::endl;
        // std::cout << "------------------------------" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}

int main()
{
    calPolyhedron<float>("off/bunny.off");
    calPolyhedron<float>("off/3holes.off");
    calPolyhedron<float>("off/elephant.off");
    return 0;
}