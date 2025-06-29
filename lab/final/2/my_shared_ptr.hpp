#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP

#include <utility>     // for std::move, std::forward
#include <cstddef>     // for std::nullptr_t
#include <type_traits> // for std::enable_if, etc.
#include <atomic>      // for std::atomic
#include <functional>  // for std::less

namespace my
{

    // 前向声明
    template <typename T>
    class weak_ptr;

    // 控制块 - 管理引用计数和对象删除
    class control_block
    {
    private:
        std::atomic<size_t> shared_count{1}; // 强引用计数
        std::atomic<size_t> weak_count{0};   // 弱引用计数

        virtual void destroy_object() noexcept = 0;
        virtual void destroy_this() noexcept = 0;

    public:
        control_block() = default;
        virtual ~control_block() = default;

        // 不允许拷贝或移动
        control_block(const control_block &) = delete;
        control_block &operator=(const control_block &) = delete;

        // 增加强引用计数
        void add_shared_ref() noexcept
        {
            shared_count.fetch_add(1, std::memory_order_relaxed);
        }

        // 增加弱引用计数
        void add_weak_ref() noexcept
        {
            weak_count.fetch_add(1, std::memory_order_relaxed);
        }

        // 减少强引用计数，如果变为0则销毁对象
        void release_shared() noexcept
        {
            if (shared_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
            {
                destroy_object();
                release_weak();
            }
        }

        // 减少弱引用计数，如果变为0且没有强引用则销毁控制块
        void release_weak() noexcept
        {
            if (weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1 && shared_count.load(std::memory_order_acquire) == 0)
            {
                destroy_this();
            }
        }

        // 获取强引用计数
        size_t use_count() const noexcept
        {
            return shared_count.load(std::memory_order_relaxed);
        }

        // 检查是否过期（没有强引用）
        bool expired() const noexcept
        {
            return use_count() == 0;
        }
    };

    // 带删除器的控制块实现
    template <typename T, typename Deleter>
    class control_block_impl : public control_block
    {
    private:
        T *ptr;
        Deleter deleter;

        void destroy_object() noexcept override
        {
            if (ptr)
            {
                deleter(ptr);
                ptr = nullptr;
            }
        }

        void destroy_this() noexcept override
        {
            delete this;
        }

    public:
        control_block_impl(T *p, Deleter d) : ptr(p), deleter(std::move(d)) {}
    };

    // 对象与控制块合一的控制块实现
    template <typename T>
    class control_block_inplace : public control_block
    {
    private:
        alignas(T) unsigned char storage[sizeof(T)];
        T *ptr;

        void destroy_object() noexcept override
        {
            if (ptr)
            {
                ptr->~T();
                ptr = nullptr;
            }
        }

        void destroy_this() noexcept override
        {
            delete this;
        }

    public:
        template <typename... Args>
        control_block_inplace(Args &&...args)
        {
            ptr = new (storage) T(std::forward<Args>(args)...);
        }

        T *get_ptr() noexcept
        {
            return ptr;
        }
    };

    // shared_ptr实现
    template <typename T>
    class shared_ptr
    {
    private:
        T *ptr = nullptr;              // 指向对象的指针
        control_block *ctrl = nullptr; // 控制块指针

        template <typename U>
        friend class shared_ptr;

        template <typename U>
        friend class weak_ptr;

        // 将相关辅助函数声明为友元，使其能访问私有成员
        template <typename U, typename... Args>
        friend shared_ptr<U> make_shared(Args &&...args);

        template <typename U, typename V>
        friend shared_ptr<U> static_pointer_cast(const shared_ptr<V> &r) noexcept;

        template <typename U, typename V>
        friend shared_ptr<U> dynamic_pointer_cast(const shared_ptr<V> &r) noexcept;

        template <typename U, typename V>
        friend shared_ptr<U> const_pointer_cast(const shared_ptr<V> &r) noexcept;

        template <typename U, typename V>
        friend shared_ptr<U> reinterpret_pointer_cast(const shared_ptr<V> &r) noexcept;

        // 私有构造函数，通过控制块和指针构造
        shared_ptr(T *p, control_block *c) noexcept : ptr(p), ctrl(c)
        {
            if (ctrl)
            {
                ctrl->add_shared_ref();
            }
        }

    public:
        using element_type = T;

        // 构造函数
        constexpr shared_ptr() noexcept = default;

        constexpr shared_ptr(std::nullptr_t) noexcept : shared_ptr() {}

        template <typename U, typename = typename std::enable_if<
                                  std::is_convertible<U *, T *>::value>::type>
        explicit shared_ptr(U *p)
        {
            if (p)
            {
                try
                {
                    ctrl = new control_block_impl<U, std::default_delete<U>>(p, std::default_delete<U>());
                    ptr = p;
                }
                catch (...)
                {
                    delete p;
                    throw;
                }
            }
        }

        template <typename U, typename Deleter, typename = typename std::enable_if<std::is_convertible<U *, T *>::value>::type>
        shared_ptr(U *p, Deleter d)
        {
            if (p)
            {
                try
                {
                    ctrl = new control_block_impl<U, Deleter>(p, std::move(d));
                    ptr = p;
                }
                catch (...)
                {
                    d(p);
                    throw;
                }
            }
        }

        // 拷贝构造函数
        shared_ptr(const shared_ptr &other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            if (ctrl)
            {
                ctrl->add_shared_ref();
            }
        }

        // 转换构造函数 - 从其他类型的shared_ptr构造
        template <typename U, typename = typename std::enable_if<
                                  std::is_convertible<U *, T *>::value>::type>
        shared_ptr(const shared_ptr<U> &other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            if (ctrl)
            {
                ctrl->add_shared_ref();
            }
        }

        // 移动构造函数
        shared_ptr(shared_ptr &&other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            other.ptr = nullptr;
            other.ctrl = nullptr;
        }

        // 从其他类型移动构造
        template <typename U, typename = typename std::enable_if<
                                  std::is_convertible<U *, T *>::value>::type>
        shared_ptr(shared_ptr<U> &&other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            other.ptr = nullptr;
            other.ctrl = nullptr;
        }

        // 从weak_ptr构造
        explicit shared_ptr(const weak_ptr<T> &other)
        {
            if (other.expired())
            {
                throw std::bad_weak_ptr();
            }
            ptr = other.ptr;
            ctrl = other.ctrl;
            ctrl->add_shared_ref();
        }

        // 析构函数
        ~shared_ptr()
        {
            if (ctrl)
            {
                ctrl->release_shared();
            }
        }

        // 赋值操作符
        shared_ptr &operator=(const shared_ptr &other) noexcept
        {
            shared_ptr(other).swap(*this);
            return *this;
        }

        template <typename U>
        shared_ptr &operator=(const shared_ptr<U> &other) noexcept
        {
            shared_ptr(other).swap(*this);
            return *this;
        }

        shared_ptr &operator=(shared_ptr &&other) noexcept
        {
            shared_ptr(std::move(other)).swap(*this);
            return *this;
        }

        template <typename U>
        shared_ptr &operator=(shared_ptr<U> &&other) noexcept
        {
            shared_ptr(std::move(other)).swap(*this);
            return *this;
        }

        // 重置函数
        void reset() noexcept
        {
            shared_ptr().swap(*this);
        }

        template <typename U>
        void reset(U *p)
        {
            shared_ptr(p).swap(*this);
        }

        template <typename U, typename Deleter>
        void reset(U *p, Deleter d)
        {
            shared_ptr(p, d).swap(*this);
        }

        // 交换函数
        void swap(shared_ptr &other) noexcept
        {
            std::swap(ptr, other.ptr);
            std::swap(ctrl, other.ctrl);
        }

        // 获取指针
        T *get() const noexcept
        {
            return ptr;
        }

        // 获取引用计数
        long use_count() const noexcept
        {
            return ctrl ? ctrl->use_count() : 0;
        }

        // 是否唯一拥有者
        bool unique() const noexcept
        {
            return use_count() == 1;
        }

        // 转换为bool
        explicit operator bool() const noexcept
        {
            return ptr != nullptr;
        }

        // 解引用操作符
        T &operator*() const noexcept
        {
            return *ptr;
        }

        // 箭头操作符
        T *operator->() const noexcept
        {
            return ptr;
        }

        // 数组索引操作符
        template <typename U = T, typename = typename std::enable_if<std::is_array<U>::value>::type>
        typename std::remove_extent<U>::type &operator[](size_t i) const
        {
            return ptr[i];
        }

        // 提供基于所有权的比较（用于排序等场景）
        bool owner_before(const shared_ptr &other) const noexcept
        {
            return std::less<control_block *>()(ctrl, other.ctrl);
        }

        bool owner_before(const weak_ptr<T> &other) const noexcept
        {
            return std::less<control_block *>()(ctrl, other.ctrl);
        }
    };

    // weak_ptr实现
    template <typename T>
    class weak_ptr
    {
    private:
        T *ptr = nullptr;
        control_block *ctrl = nullptr;

        template <typename U>
        friend class shared_ptr;

        template <typename U>
        friend class weak_ptr;

    public:
        // 构造函数
        constexpr weak_ptr() noexcept = default;

        // 拷贝构造函数
        weak_ptr(const weak_ptr &other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            if (ctrl)
            {
                ctrl->add_weak_ref();
            }
        }

        // 从shared_ptr构造
        weak_ptr(const shared_ptr<T> &other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            if (ctrl)
            {
                ctrl->add_weak_ref();
            }
        }

        // 从其他类型weak_ptr构造
        template <typename U, typename = typename std::enable_if<
                                  std::is_convertible<U *, T *>::value>::type>
        weak_ptr(const weak_ptr<U> &other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            if (ctrl)
            {
                ctrl->add_weak_ref();
            }
        }

        // 移动构造函数
        weak_ptr(weak_ptr &&other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            other.ptr = nullptr;
            other.ctrl = nullptr;
        }

        // 从其他类型移动构造
        template <typename U, typename = typename std::enable_if<
                                  std::is_convertible<U *, T *>::value>::type>
        weak_ptr(weak_ptr<U> &&other) noexcept : ptr(other.ptr), ctrl(other.ctrl)
        {
            other.ptr = nullptr;
            other.ctrl = nullptr;
        }

        // 析构函数
        ~weak_ptr()
        {
            if (ctrl)
            {
                ctrl->release_weak();
            }
        }

        // 赋值操作符
        weak_ptr &operator=(const weak_ptr &other) noexcept
        {
            weak_ptr(other).swap(*this);
            return *this;
        }

        weak_ptr &operator=(weak_ptr &&other) noexcept
        {
            weak_ptr(std::move(other)).swap(*this);
            return *this;
        }

        template <typename U>
        weak_ptr &operator=(const weak_ptr<U> &other) noexcept
        {
            weak_ptr(other).swap(*this);
            return *this;
        }

        template <typename U>
        weak_ptr &operator=(weak_ptr<U> &&other) noexcept
        {
            weak_ptr(std::move(other)).swap(*this);
            return *this;
        }

        weak_ptr &operator=(const shared_ptr<T> &other) noexcept
        {
            weak_ptr(other).swap(*this);
            return *this;
        }

        // 重置函数
        void reset() noexcept
        {
            if (ctrl)
            {
                ctrl->release_weak();
                ptr = nullptr;
                ctrl = nullptr;
            }
        }

        // 交换函数
        void swap(weak_ptr &other) noexcept
        {
            std::swap(ptr, other.ptr);
            std::swap(ctrl, other.ctrl);
        }

        // 获取引用计数
        long use_count() const noexcept
        {
            return ctrl ? ctrl->use_count() : 0;
        }

        // 检查是否过期
        bool expired() const noexcept
        {
            return use_count() == 0;
        }

        // 获取shared_ptr
        shared_ptr<T> lock() const noexcept
        {
            if (expired())
            {
                return shared_ptr<T>();
            }
            return shared_ptr<T>(ptr, ctrl);
        }

        // 提供基于所有权的比较
        bool owner_before(const weak_ptr &other) const noexcept
        {
            return std::less<control_block *>()(ctrl, other.ctrl);
        }

        bool owner_before(const shared_ptr<T> &other) const noexcept
        {
            return std::less<control_block *>()(ctrl, other.ctrl);
        }
    };

    // 辅助函数 make_shared
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args &&...args)
    {
        auto cb = new control_block_inplace<T>(std::forward<Args>(args)...);
        auto ptr = cb->get_ptr();

        shared_ptr<T> result;
        result.ptr = ptr;
        result.ctrl = cb;

        return result;
    }

    // 比较操作符
    template <typename T, typename U>
    bool operator==(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
    {
        return lhs.get() == rhs.get();
    }

    template <typename T, typename U>
    bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T>
    bool operator==(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
    {
        return !lhs;
    }

    template <typename T>
    bool operator==(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
    {
        return !rhs;
    }

    template <typename T>
    bool operator!=(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
    {
        return static_cast<bool>(lhs);
    }

    template <typename T>
    bool operator!=(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
    {
        return static_cast<bool>(rhs);
    }

    // 特化swap
    template <typename T>
    void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    template <typename T>
    void swap(weak_ptr<T> &lhs, weak_ptr<T> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    // 静态转换
    template <typename T, typename U>
    shared_ptr<T> static_pointer_cast(const shared_ptr<U> &r) noexcept
    {
        auto p = static_cast<T *>(r.get());
        return shared_ptr<T>(p, r.ctrl);
    }

    // 动态转换
    template <typename T, typename U>
    shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &r) noexcept
    {
        if (auto p = dynamic_cast<T *>(r.get()))
        {
            return shared_ptr<T>(p, r.ctrl);
        }
        return shared_ptr<T>();
    }

    // const转换
    template <typename T, typename U>
    shared_ptr<T> const_pointer_cast(const shared_ptr<U> &r) noexcept
    {
        auto p = const_cast<T *>(r.get());
        return shared_ptr<T>(p, r.ctrl);
    }

    // reinterpret转换
    template <typename T, typename U>
    shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U> &r) noexcept
    {
        auto p = reinterpret_cast<T *>(r.get());
        return shared_ptr<T>(p, r.ctrl);
    }

} // namespace my

#endif // MY_SHARED_PTR_HPP
