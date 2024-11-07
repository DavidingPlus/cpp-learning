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

    // C++ 11 不支持直接以 auto 作为函数的返回值，需要加上 decltype 进行推断。
    auto operator()(const T &val, Args &&...args)
        -> decltype(val + LSum<Args...>()(std::forward<Args>(args)...))
    {
        // 完美转发，保证参数类型能够正确接受。
        // 有且仅在使用右值引用 && 的时候使用。（目前还是有点懵懂，后续研究）
        // 参考文章：https://blog.csdn.net/kelvin_yin/article/details/138551173
        return val + LSum<Args...>()(std::forward<Args>(args)...);
    }
};

template <typename T>
struct LSum<T>
{

    auto operator()(const T &val)
        -> decltype(val) { return val; }
};


// 辅助函数，封装成为函数模板。
template <typename... Args>
auto sum(Args &&...args)
    -> decltype(LSum<Args...>()(std::forward<Args>(args)...))
{
    return LSum<Args...>()(std::forward<Args>(args)...);
}


#endif
