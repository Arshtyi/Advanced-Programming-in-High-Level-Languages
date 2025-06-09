#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <vector>
void showMemoryInfo()
{
    std::cout << "当前系统内存信息：" << std::endl;
    std::cout << "- 最大可分配大小: " << (size_t)-1 << " 字节" << std::endl;
}
size_t tryAllocate(size_t size)
{
    std::cout << "尝试分配 " << size << " 字节内存..." << std::endl;
    try
    {
        char *buffer = new char[size];
        for (size_t i = 0; i < size; i += 1024 * 1024)
        {
            buffer[i] = 'x';
        }
        std::cout << "分配 " << size << " 字节内存" << std::endl;
        delete[] buffer;
        return size;
    }
    catch (const std::exception &e)
    {
        std::cout << "✗ 内存分配失败: " << e.what() << std::endl;
        throw; // 重新抛出异常
    }
}
size_t findMaxAllocation()
{
    size_t low = 1024 * 1024;
    size_t high = (size_t)-1 / 2;
    size_t maxSuccessful = 0;
    std::cout << "开始二分查找最大可分配内存..." << std::endl;
    while (low <= high)
    {
        size_t mid = low + (high - low) / 2;
        try
        {
            tryAllocate(mid);
            maxSuccessful = mid;
            low = mid + 1;
        }
        catch (const std::exception &)
        {
            high = mid - 1;
        }
    }
    return maxSuccessful;
}

int main()
{
    std::cout << "===== 测试内存分配 =====" << std::endl;
    showMemoryInfo();
    std::cout << "\n==== 二分查找最大可分配内存 =====" << std::endl;
    try
    {
        size_t maxMem = findMaxAllocation();
        std::cout << "\n结果：最大可分配内存约为 " << maxMem << " 字节" << std::endl;
        std::cout << "      约等于 " << (double)maxMem / (1024 * 1024 * 1024) << " GB" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "在查找过程中发生错误: " << e.what() << std::endl;
    }
    return 0;
}