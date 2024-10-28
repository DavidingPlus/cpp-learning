#ifndef _SUM_H_
#define _SUM_H_

// copy from ./snippet/CppThreadLearning/FutureTest/sum.h


template <typename T, typename... Args>
struct LSum
{

    auto operator()(const T &val, Args &&...args)
        -> decltype(val + LSum<Args...>()(std::forward<Args>(args)...)) { return val + LSum<Args...>()(std::forward<Args>(args)...); }
};

template <typename T>
struct LSum<T>
{

    auto operator()(const T &val)
        -> decltype(val) { return val; }
};


template <typename... Args>
auto sum(Args &&...args)
    -> decltype(LSum<Args...>()(std::forward<Args>(args)...))
{
    return LSum<Args...>()(std::forward<Args>(args)...);
}


#endif
