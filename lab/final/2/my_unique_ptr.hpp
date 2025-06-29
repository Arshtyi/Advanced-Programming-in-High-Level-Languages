#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP

#include <utility>     // for std::move, std::forward
#include <type_traits> // for std::remove_reference, std::enable_if

namespace my
{

    // 默认删除器
    template <typename T>
    struct default_delete
    {
        constexpr default_delete() noexcept = default;

        template <typename U, typename = typename std::enable_if<std::is_convertible<U *, T *>::value>::type>
        default_delete(const default_delete<U> &) noexcept {}

        void operator()(T *ptr) const noexcept
        {
            static_assert(sizeof(T) > 0, "不能删除不完整类型");
            delete ptr;
        }
    };

    // 数组类型的特化版本
    template <typename T>
    struct default_delete<T[]>
    {
        constexpr default_delete() noexcept = default;

        template <typename U, typename = typename std::enable_if<std::is_convertible<U (*)[], T (*)[]>::value>::type>
        default_delete(const default_delete<U[]> &) noexcept {}

        void operator()(T *ptr) const noexcept
        {
            static_assert(sizeof(T) > 0, "不能删除不完整类型");
            delete[] ptr;
        }
    };

    // unique_ptr 主模板（单对象版本）
    template <typename T, typename Deleter = default_delete<T>>
    class unique_ptr
    {
    public:
        using pointer = T *;
        using element_type = T;
        using deleter_type = Deleter;

        // 构造函数
        constexpr unique_ptr() noexcept : ptr_(nullptr), deleter_() {}

        constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr() {}

        explicit unique_ptr(pointer p) noexcept : ptr_(p), deleter_() {}

        unique_ptr(pointer p, const Deleter &d) noexcept : ptr_(p), deleter_(d) {}

        unique_ptr(pointer p, Deleter &&d) noexcept : ptr_(p), deleter_(std::move(d)) {}

        // 移动构造
        unique_ptr(unique_ptr &&u) noexcept : ptr_(u.ptr_), deleter_(std::move(u.deleter_))
        {
            u.ptr_ = nullptr;
        }

        // 允许从派生类转换到基类的移动构造
        template <typename U, typename E, typename = typename std::enable_if<std::is_convertible<U *, T *>::value && std::is_convertible<E, Deleter>::value>::type>
        unique_ptr(unique_ptr<U, E> &&u) noexcept
            : ptr_(u.release()), deleter_(std::move(u.get_deleter())) {}

        // 禁用拷贝构造
        unique_ptr(const unique_ptr &) = delete;

        // 析构函数
        ~unique_ptr()
        {
            if (ptr_)
            {
                deleter_(ptr_);
            }
        }

        // 移动赋值运算符
        unique_ptr &operator=(unique_ptr &&u) noexcept
        {
            if (this != &u)
            {
                reset(u.release());
                deleter_ = std::move(u.deleter_);
            }
            return *this;
        }

        // 从派生类转换到基类的移动赋值
        template <typename U, typename E, typename = typename std::enable_if<std::is_convertible<U *, T *>::value && std::is_convertible<E, Deleter>::value>::type>
        unique_ptr &operator=(unique_ptr<U, E> &&u) noexcept
        {
            reset(u.release());
            deleter_ = std::move(u.get_deleter());
            return *this;
        }

        // nullptr赋值
        unique_ptr &operator=(std::nullptr_t) noexcept
        {
            reset();
            return *this;
        }

        // 禁用拷贝赋值
        unique_ptr &operator=(const unique_ptr &) = delete;

        // 访问器
        pointer get() const noexcept
        {
            return ptr_;
        }

        deleter_type &get_deleter() noexcept
        {
            return deleter_;
        }

        const deleter_type &get_deleter() const noexcept
        {
            return deleter_;
        }

        explicit operator bool() const noexcept
        {
            return ptr_ != nullptr;
        }

        // 解引用操作符
        typename std::add_lvalue_reference<T>::type operator*() const
        {
            return *ptr_;
        }

        pointer operator->() const noexcept
        {
            return ptr_;
        }

        // 修改器
        pointer release() noexcept
        {
            pointer p = ptr_;
            ptr_ = nullptr;
            return p;
        }

        void reset(pointer p = nullptr) noexcept
        {
            pointer old_ptr = ptr_;
            ptr_ = p;
            if (old_ptr)
            {
                deleter_(old_ptr);
            }
        }

        void swap(unique_ptr &other) noexcept
        {
            std::swap(ptr_, other.ptr_);
            std::swap(deleter_, other.deleter_);
        }

    private:
        pointer ptr_;
        deleter_type deleter_;

        // 允许不同类型的unique_ptr访问私有成员
        template <typename U, typename E>
        friend class unique_ptr;
    };

    // 数组特化版本
    template <typename T, typename Deleter>
    class unique_ptr<T[], Deleter>
    {
    public:
        using pointer = T *;
        using element_type = T;
        using deleter_type = Deleter;

        // 构造函数
        constexpr unique_ptr() noexcept : ptr_(nullptr), deleter_() {}

        constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr() {}

        explicit unique_ptr(pointer p) noexcept : ptr_(p), deleter_() {}

        unique_ptr(pointer p, const Deleter &d) noexcept : ptr_(p), deleter_(d) {}

        unique_ptr(pointer p, Deleter &&d) noexcept : ptr_(p), deleter_(std::move(d)) {}

        // 移动构造
        unique_ptr(unique_ptr &&u) noexcept : ptr_(u.ptr_), deleter_(std::move(u.deleter_))
        {
            u.ptr_ = nullptr;
        }

        // 禁用拷贝构造
        unique_ptr(const unique_ptr &) = delete;

        // 析构函数
        ~unique_ptr()
        {
            if (ptr_)
            {
                deleter_(ptr_);
            }
        }

        // 移动赋值运算符
        unique_ptr &operator=(unique_ptr &&u) noexcept
        {
            if (this != &u)
            {
                reset(u.release());
                deleter_ = std::move(u.deleter_);
            }
            return *this;
        }

        // nullptr赋值
        unique_ptr &operator=(std::nullptr_t) noexcept
        {
            reset();
            return *this;
        }

        // 禁用拷贝赋值
        unique_ptr &operator=(const unique_ptr &) = delete;

        // 访问器
        pointer get() const noexcept
        {
            return ptr_;
        }

        deleter_type &get_deleter() noexcept
        {
            return deleter_;
        }

        const deleter_type &get_deleter() const noexcept
        {
            return deleter_;
        }

        explicit operator bool() const noexcept
        {
            return ptr_ != nullptr;
        }

        // 数组版本特有的下标操作符
        T &operator[](size_t i) const
        {
            return ptr_[i];
        }

        // 修改器
        pointer release() noexcept
        {
            pointer p = ptr_;
            ptr_ = nullptr;
            return p;
        }

        void reset(pointer p = nullptr) noexcept
        {
            pointer old_ptr = ptr_;
            ptr_ = p;
            if (old_ptr)
            {
                deleter_(old_ptr);
            }
        }

        void swap(unique_ptr &other) noexcept
        {
            std::swap(ptr_, other.ptr_);
            std::swap(deleter_, other.deleter_);
        }

    private:
        pointer ptr_;
        deleter_type deleter_;
    };

    // 单对象版本的make_unique
    template <typename T, typename... Args>
    typename std::enable_if<!std::is_array<T>::value, unique_ptr<T>>::type
    make_unique(Args &&...args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // 数组版本的make_unique
    template <typename T>
    typename std::enable_if<std::is_array<T>::value, unique_ptr<T>>::type
    make_unique(size_t size)
    {
        using ElementType = typename std::remove_extent<T>::type;
        return unique_ptr<T>(new ElementType[size]());
    }

    // 比较操作符
    template <typename T1, typename D1, typename T2, typename D2>
    bool operator==(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return x.get() == y.get();
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator!=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return x.get() != y.get();
    }

    template <typename T, typename D>
    bool operator==(const unique_ptr<T, D> &x, std::nullptr_t) noexcept
    {
        return !x;
    }

    template <typename T, typename D>
    bool operator==(std::nullptr_t, const unique_ptr<T, D> &y) noexcept
    {
        return !y;
    }

    template <typename T, typename D>
    bool operator!=(const unique_ptr<T, D> &x, std::nullptr_t) noexcept
    {
        return static_cast<bool>(x);
    }

    template <typename T, typename D>
    bool operator!=(std::nullptr_t, const unique_ptr<T, D> &y) noexcept
    {
        return static_cast<bool>(y);
    }

    // 特化swap
    template <typename T, typename D>
    void swap(unique_ptr<T, D> &x, unique_ptr<T, D> &y) noexcept
    {
        x.swap(y);
    }

} // namespace my

#endif // MY_UNIQUE_PTR_HPP
