#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <cassert>

#include "my_unique_ptr.hpp"
#include "my_shared_ptr.hpp"

class Resource
{
private:
    std::string name;
    static int counter;

public:
    Resource(const std::string &n = "未命名资源") : name(n)
    {
        counter++;
        std::cout << "构造资源 [" << name << "], 当前资源数: " << counter << std::endl;
    }

    ~Resource()
    {
        counter--;
        std::cout << "销毁资源 [" << name << "], 剩余资源数: " << counter << std::endl;
    }

    void use() const
    {
        std::cout << "使用资源 [" << name << "]" << std::endl;
    }

    std::string getName() const
    {
        return name;
    }

    static int getCount()
    {
        return counter;
    }
};

int Resource::counter = 0;

// 用于测试自定义删除器
struct ResourceDeleter
{
    void operator()(Resource *p) const
    {
        std::cout << "使用自定义删除器销毁资源 [" << p->getName() << "]" << std::endl;
        delete p;
    }
};

// 测试my_unique_ptr
void test_my_unique_ptr()
{
    std::cout << "\n=== 测试 my_unique_ptr ===\n"
              << std::endl;

    // 基本构造和析构
    {
        std::cout << "1. 基本构造和析构：" << std::endl;
        my::unique_ptr<Resource> p1(new Resource("unique_ptr资源1"));
        p1->use();
        std::cout << "资源指针: " << p1.get() << std::endl;
        std::cout << std::boolalpha << "p1是否为空: " << !p1 << std::endl;
    } // p1在这里自动销毁

    // 移动语义
    {
        std::cout << "\n2. 移动语义：" << std::endl;
        my::unique_ptr<Resource> p1(new Resource("移动前资源"));
        std::cout << "p1指针: " << p1.get() << std::endl;

        my::unique_ptr<Resource> p2 = std::move(p1);
        std::cout << "移动后p1指针: " << p1.get() << std::endl;
        std::cout << "移动后p2指针: " << p2.get() << std::endl;

        assert(p1.get() == nullptr);
        assert(p2.get() != nullptr);
        p2->use();
    }

    // 自定义删除器
    {
        std::cout << "\n3. 自定义删除器：" << std::endl;
        my::unique_ptr<Resource, ResourceDeleter> p(new Resource("自定义删除器资源"), ResourceDeleter());
        p->use();
    }

    // release和reset
    {
        std::cout << "\n4. release和reset：" << std::endl;
        my::unique_ptr<Resource> p1(new Resource("release测试"));

        // release会释放所有权但不销毁资源
        Resource *raw = p1.release();
        std::cout << "p1指针(release后): " << p1.get() << std::endl;
        std::cout << "raw指针: " << raw << std::endl;

        // 重新获取所有权
        my::unique_ptr<Resource> p2;
        p2.reset(raw);
        std::cout << "p2指针(reset后): " << p2.get() << std::endl;

        // reset为nullptr会销毁资源
        p2.reset();
        std::cout << "p2指针(reset(nullptr)后): " << p2.get() << std::endl;
    }

    // 数组形式
    {
        std::cout << "\n5. 数组形式：" << std::endl;
        my::unique_ptr<Resource[]> arr(new Resource[3]{
            Resource("数组元素0"),
            Resource("数组元素1"),
            Resource("数组元素2")});

        for (int i = 0; i < 3; ++i)
        {
            arr[i].use();
        }
    }

    // make_unique
    {
        std::cout << "\n6. make_unique：" << std::endl;
        auto p = my::make_unique<Resource>("make_unique创建的资源");
        p->use();

        auto arr = my::make_unique<Resource[]>(2);
        arr[0].use();
        arr[1].use();
    }
}

// 测试my_shared_ptr
void test_my_shared_ptr()
{
    std::cout << "\n=== 测试 my_shared_ptr ===\n"
              << std::endl;

    // 基本构造和引用计数
    {
        std::cout << "1. 基本构造和引用计数：" << std::endl;
        my::shared_ptr<Resource> p1(new Resource("shared_ptr资源1"));
        std::cout << "p1引用计数: " << p1.use_count() << std::endl;

        {
            my::shared_ptr<Resource> p2 = p1;
            std::cout << "复制后 p1引用计数: " << p1.use_count() << std::endl;
            std::cout << "p2引用计数: " << p2.use_count() << std::endl;

            my::shared_ptr<Resource> p3 = p1;
            std::cout << "再次复制后 p1引用计数: " << p1.use_count() << std::endl;

            p3.reset();
            std::cout << "p3.reset()后 p1引用计数: " << p1.use_count() << std::endl;
        }

        std::cout << "内部作用域结束后 p1引用计数: " << p1.use_count() << std::endl;
        p1->use();
    }

    // 移动语义
    {
        std::cout << "\n2. 移动语义：" << std::endl;
        my::shared_ptr<Resource> p1(new Resource("shared移动资源"));
        std::cout << "移动前 p1引用计数: " << p1.use_count() << std::endl;

        my::shared_ptr<Resource> p2 = std::move(p1);
        std::cout << "移动后 p1指针: " << p1.get() << ", 引用计数: " << p1.use_count() << std::endl;
        std::cout << "移动后 p2指针: " << p2.get() << ", 引用计数: " << p2.use_count() << std::endl;

        assert(p1.get() == nullptr);
        assert(p2.get() != nullptr);
        assert(p2.use_count() == 1);
    }

    // make_shared
    {
        std::cout << "\n3. make_shared：" << std::endl;
        auto p = my::make_shared<Resource>("make_shared创建的资源");
        std::cout << "p引用计数: " << p.use_count() << std::endl;
        p->use();
    }

    // weak_ptr
    {
        std::cout << "\n4. weak_ptr：" << std::endl;
        my::shared_ptr<Resource> sp = my::make_shared<Resource>("weak_ptr测试资源");

        my::weak_ptr<Resource> wp = sp;
        std::cout << "weak_ptr创建后，shared_ptr引用计数: " << sp.use_count() << std::endl;

        {
            // 从weak_ptr获取shared_ptr
            auto sp2 = wp.lock();
            if (sp2)
            {
                std::cout << "weak_ptr成功锁定资源，引用计数: " << sp2.use_count() << std::endl;
                sp2->use();
            }
        }

        // 重置shared_ptr，资源应该被释放
        sp.reset();
        std::cout << "shared_ptr重置后，weak_ptr是否过期: " << wp.expired() << std::endl;

        // 尝试获取已释放的资源
        auto sp3 = wp.lock();
        if (!sp3)
        {
            std::cout << "weak_ptr无法锁定已释放的资源" << std::endl;
        }
    }

    // 自定义删除器
    {
        std::cout << "\n5. 自定义删除器：" << std::endl;
        my::shared_ptr<Resource> p(new Resource("shared_ptr自定义删除器资源"), ResourceDeleter());
        p->use();
    }

    // 线程安全性
    {
        std::cout << "\n6. 线程安全性：" << std::endl;
        auto sp = my::make_shared<Resource>("线程共享资源");

        auto thread_func = [sp](int id)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
            std::cout << "线程 " << id << " 使用资源，引用计数: " << sp.use_count() << std::endl;
            sp->use();
        };

        std::vector<std::thread> threads;
        for (int i = 0; i < 5; ++i)
        {
            threads.emplace_back(thread_func, i);
        }

        for (auto &t : threads)
        {
            t.join();
        }
    }

    // 类型转换
    {
        struct Base
        {
            virtual ~Base() { std::cout << "~Base()" << std::endl; }
            virtual void foo() { std::cout << "Base::foo()" << std::endl; }
        };

        struct Derived : public Base
        {
            void foo() override { std::cout << "Derived::foo()" << std::endl; }
        };

        std::cout << "\n7. 指针类型转换：" << std::endl;

        // 上行转换
        my::shared_ptr<Derived> derived = my::make_shared<Derived>();
        my::shared_ptr<Base> base = derived;
        std::cout << "上行转换后，base引用计数: " << base.use_count() << std::endl;
        base->foo();

        // 使用各种类型转换
        derived = my::make_shared<Derived>();
        base = derived;

        // dynamic_cast
        auto derived2 = my::dynamic_pointer_cast<Derived>(base);
        if (derived2)
        {
            std::cout << "dynamic_cast成功，引用计数: " << derived2.use_count() << std::endl;
            derived2->foo();
        }
    }
}

int main()
{
    std::cout << "===== 智能指针测试程序 =====" << std::endl;

    test_my_unique_ptr();

    std::cout << "\n\n";

    test_my_shared_ptr();

    std::cout << "\n===== 测试完成 =====" << std::endl;
    return 0;
}
