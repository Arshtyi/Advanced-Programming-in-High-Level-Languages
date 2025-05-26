#ifndef FACET_H
#define FACET_H
#include <vector>
#include "Point.hpp"
template <typename T>
class Polyhedron;
template <typename T>
class Facet
{
private:
    std::vector<Point<T> *> vertices;

public:
    Facet() {}
    T area() const
    {
        if (vertices.size() < 3)
            return 0;
        T totalArea = 0;
        for (size_t i = 1; i < vertices.size() - 1; i++)
        {
            // 计算三角形 {vertices[0], vertices[i], vertices[i+1]} 的面积
            Point<T> *p0 = vertices[0];
            Point<T> *p1 = vertices[i];
            Point<T> *p2 = vertices[i + 1];

            T a = p0->distance(p1);
            T b = p1->distance(p2);
            T c = p2->distance(p0);

            // Heron公式
            T s = (a + b + c) / 2;
            T area = std::sqrt(s * (s - a) * (s - b) * (s - c));
            totalArea += area;
        }

        return totalArea;
    }

    friend class Polyhedron<T>;
};

#endif // FACET_H
