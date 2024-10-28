#ifndef _SUM_H_
#define _SUM_H_


// 项目环境是 C++ 11，因此这个注释掉。
// template <typename... Args>
// auto sum(Args &&...args)
// {
//     // C++ 17 折叠表达式
//     // "0 +" 避免空参数包错误
//     return (0 + ... + args);
// }


// 我不想使用重载来实现递归出口，想使用特化，因此需要使用类模板，而非单纯的函数模板。

template <typename T, typename... Args>
struct LSum
{

    auto operator()(const T &val, Args &&...args) { return val + LSum<Args...>()(args...); }
};


template <typename T>
struct LSum<T>
{

    auto operator()(const T &val) { return val; }
}

// 辅助函数，封装成为函数模板。

template <typename... Args>
auto sum(Args &&...args)
{
    return LSum<Args...>()(args...);
}


#endif
