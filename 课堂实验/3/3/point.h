class Point
{ // Point 类的定义

public:
    Point(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    } // 构造函数，内联

    Point(const Point &p); // 复制构造函数

    void setX(int xx) { x = xx; }

    void setY(int yy) { y = yy; }

    int getX() const { return x; } // 常函数（第5章）

    int getY() const { return y; } // 常函数（第5章）

private:
    int x, y; // 私有数据
};
void fun1(Point p);

Point fun2();