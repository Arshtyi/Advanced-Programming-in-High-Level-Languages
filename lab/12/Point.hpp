#ifndef POINT_H
#define POINT_H
#include <cmath>
template <typename T>
class Polyhedron;
template <typename T>
class Point
{
private:
    T x, y, z;

public:
    Point(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    T getX() const { return x; }
    T getY() const { return y; }
    T getZ() const { return z; }
    T distance(Point<T> *p) const
    {
        T dx = x - p->x;
        T dy = y - p->y;
        T dz = z - p->z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
    friend class Polyhedron<T>;
};

#endif // POINT_H
