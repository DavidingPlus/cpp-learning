#ifndef __HASHFUNCTION__
#define __HASHFUNCTION__

#include <iostream>
class HashFunction {
public:
    // 三个重载
    // 拆解(递归)参数包
    template <typename... Types>  // ... 的含义 接受任意数量的模板参数
    inline size_t hash_val(const Types &...args) {
        size_t seed = 0;
        hash_val(seed, args...);
        return seed;
    }

private:
    template <typename Type, typename... Types>
    inline void hash_val(size_t &seed, const Type &val, const Types &...args) {
        hash_combine(seed, val);
        hash_val(seed, args...);
    }

    template <typename Type>
    inline void hash_val(size_t &seed, const Type &val) {
        hash_combine(seed, val);
    }

    template <typename Type>
    inline void hash_combine(size_t &seed, const Type &val) {
        seed ^= std::hash<Type>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        // 据说这个丑陋的数字是黄金比例的数字
    }
};

#endif
