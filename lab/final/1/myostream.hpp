#ifndef MYOSTREAM_HPP
#define MYOSTREAM_HPP

#include <string>
#include <cstdio>
#include <iomanip>

class myostream
{
private:
    int width_ = 0;            // 字段宽度
    int precision_ = 6;        // 浮点精度
    bool left_align_ = false;  // 左对齐
    bool right_align_ = false; // 右对齐

public:
    myostream() = default;
    // 重载 <<
    // char
    myostream &operator<<(const char c)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%dc", width_);
            }
            else
            {
                sprintf(format, "%%%dc", width_);
            }
            printf(format, c);
        }
        else
        {
            printf("%c", c);
        }
        return *this;
    }

    // int
    myostream &operator<<(const int n)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%dd", width_);
            }
            else
            {
                sprintf(format, "%%%dd", width_);
            }
            printf(format, n);
        }
        else
        {
            printf("%d", n);
        }
        return *this;
    }

    // float
    myostream &operator<<(const float f)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%d.%df", width_, precision_);
            }
            else
            {
                sprintf(format, "%%%d.%df", width_, precision_);
            }
            printf(format, f);
        }
        else
        {
            char format[20];
            sprintf(format, "%%.%df", precision_);
            printf(format, f);
        }
        return *this;
    }

    // double
    myostream &operator<<(const double d)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%d.%dlf", width_, precision_);
            }
            else
            {
                sprintf(format, "%%%d.%dlf", width_, precision_);
            }
            printf(format, d);
        }
        else
        {
            char format[20];
            sprintf(format, "%%.%dlf", precision_);
            printf(format, d);
        }
        return *this;
    }

    // std::string
    myostream &operator<<(const std::string &s)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%ds", width_);
            }
            else
            {
                sprintf(format, "%%%ds", width_);
            }
            printf(format, s.c_str());
        }
        else
        {
            printf("%s", s.c_str());
        }
        return *this;
    }

    // const char* 类型
    myostream &operator<<(const char *s)
    {
        if (width_ > 0)
        {
            char format[20];
            if (left_align_)
            {
                sprintf(format, "%%-%ds", width_);
            }
            else
            {
                sprintf(format, "%%%ds", width_);
            }
            printf(format, s);
        }
        else
        {
            printf("%s", s);
        }
        return *this;
    }

    // 设置字段宽度
    myostream &setw(int w)
    {
        width_ = w;
        return *this;
    }

    // 设置宽度（setw的别名）
    myostream &width(int w)
    {
        return setw(w);
    }

    // 设置精度
    myostream &setprecision(int p)
    {
        precision_ = p;
        return *this;
    }

    // 设置左对齐
    myostream &left()
    {
        left_align_ = true;
        right_align_ = false;
        return *this;
    }

    // 设置右对齐
    myostream &right()
    {
        right_align_ = true;
        left_align_ = false;
        return *this;
    }

    // 重置宽度设置
    myostream &resetw()
    {
        width_ = 0;
        return *this;
    }

    // 重置精度设置
    myostream &resetprecision()
    {
        precision_ = 6; // 默认精度为6
        return *this;
    }

    // 重置对齐设置
    myostream &resetalign()
    {
        left_align_ = false;
        right_align_ = false;
        return *this;
    }

    // 重置所有格式设置
    myostream &reset()
    {
        width_ = 0;
        precision_ = 6;
        left_align_ = false;
        right_align_ = false;
        return *this;
    }
};

#endif // MYOSTREAM_HPP