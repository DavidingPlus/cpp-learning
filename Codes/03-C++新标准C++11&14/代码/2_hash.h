#ifndef __HASH__
#define __HASH__

#include <iostream>
using namespace std;

// 定义万用的哈希函数
class GetHashCode
{
public:
    // 接受参数包
    template <typename... Types>
    inline size_t HashCode(const Types &...args)
    {
        size_t seed = 0;
        ChangeSeed(seed, args...);
        return seed;
    }

private:
    template <typename Type>
    inline void ChangeSeed(size_t &seed, const Type &val)
    {
        seed ^= hash<Type>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    // 重载这个函数对seed进行修改
    template <typename Type, typename... Types>
    inline void ChangeSeed(size_t &seed, const Type &val, const Types &...args)
    {
        ChangeSeed(seed, val);     // 处理该val
        ChangeSeed(seed, args...); // 处理剩余的参数包
    }
};

#endif