// sum.cpp
#include <cstdarg>
#include <iostream>

// 方法1
template <typename T>
// auto sum(int count, T v0, ...) { // C style
auto sum(int count, T v0...) {  // C++ style
    va_list args;

    va_start(args, v0);

    auto s = v0;
    while (count-- > 0) s += va_arg(args, T);

    va_end(args);

    return s;
}

// 老白的写法，方法2，没看懂
template <typename... Args>
auto sum2(Args... args) {
    // std::cout << sizeof...(args) << std::endl;

    return (0 + ... + args);
}

// 方法3，出问题了
template <typename value_type, typename... Args>
auto sum3(value_type val, Args... args) {
    return val + sum2(args...);
}

// 特化版本
auto sum3() {
    return 0;
}

int main() {
    // C风格的参数一般第一个参数都会给出参数包的个数，后面才是数据
    std::cout << sum(4, 1, 2, 3, 4, 5) << std::endl;

    std::cout << sum2(1, 2, 3, 4, 5) << std::endl;

    std::cout << sum3(1, 2, 3, 4, 5) << std::endl;

    return 0;
}
