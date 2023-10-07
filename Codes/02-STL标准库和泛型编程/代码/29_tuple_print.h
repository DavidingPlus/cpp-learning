#ifndef __TUPLEPRINT__
#define __TUPLEPRINT__

#include <iostream>
using namespace std;

// get<> 尖括号里面不能放入变量，只能放入一个常量!!!!
template <typename Tuple, size_t N>
struct tuple_print
{
    inline static void print(const Tuple &t, ostream &out)
    {
        tuple_print<Tuple, N - 1>::print(t, out);
        out << ' ' << get<N - 1>(t);
        // 为什么要反着写？
        // 因为递归出来打印的顺序是从0 到 n-1!!!!
    }
};

// 递归出口
template <typename Tuple>
struct tuple_print<Tuple, 1>
{
    inline static void print(const Tuple &t, ostream &out)
    {
        out << get<0>(t);
    }
};

// 重载 左移运算符
#include <tuple>
template <typename... Types>
inline ostream &
operator<<(ostream &out, const tuple<Types...> &t)
{
    // decltype 可以得出变量的类型
    // 模板参数里面可以放入一个常量，根据常量不同的大小可以调用不同的重载或者特化版本
    tuple_print<decltype(t), sizeof...(Types)>::print(t, out);
    return out;
}

#endif
