#include <iostream>
using namespace std;
#include <hashtable.h>
#include <cstring>

struct eqstr
{
    bool operator()(const char *str1, const char *str2) const
    {
        return strcmp(str1, str2) == 0;
    }
};

// 如果是自己设计就可以这么设计
inline size_t _hash_string(const char *s)
{
    size_t ret = 0;
    for (; *s != '\n'; ++s)
        ret = 10 * ret + *s;
    return ret;
}

template <class Type>
struct fuck
{
};

// 特化版本
template <>
struct fuck<const char *>
{
    size_t operator()(const char *s) const { return _hash_string(s); }
};

template <>
struct fuck<char *>
{
    size_t operator()(char *s) const { return _hash_string(s); }
};

// // 偏特化版本
// template <class Fuck>
// struct fuck<Fuck *>
// {
//     size_t operator()(Fuck *s) const { return _hash_string(s); }
// };

int main()
{
    __gnu_cxx::hashtable<const char *, const char *,
                         fuck<const char *>, // 标准库没有提供 hash<std::string>!!!!
                         _Identity<const char *>,
                         eqstr>                // 不能直接放入strcmp，因为我们需要判断是否相同，返回的是true和false;而strcmp返回的是1 0 -1，接口不太一致
        ht(53, fuck<const char *>(), eqstr()); // 这个东西没有默认空的构造函数，需要提供一些东西
    // 第一个参数是初始篮子的设置大小
    // 从这里可以看出直接使用hashtable非常难用

    ht.insert_unique("kiwi31231231");
    ht.insert_unique("plum");
    ht.insert_unique("apple");
    for (auto &val : ht)
        cout << val << endl;

    // cout << hash<int>()(32) << endl;

    return 0;
}
