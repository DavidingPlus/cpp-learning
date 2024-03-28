//sum.cpp

#include <iostream>
#include <cstdarg>

template <typename T>
// auto sum(int count, T v0, ...) { // C style
auto sum(int count, T v0...) { // C++ style
    va_list args;

    va_start(args, v0);

    auto s = v0;
    while (count-- > 0) s += va_arg(args, T);

    va_end(args);

    return s;
}

template <typename ...types>
auto sum2(types ...args) {
    std::cout << sizeof...(args) << std::endl;
    return (0 + ... + args);
}

int main() {
    std::cout << sum(4, 1, 2, 3, 4) << std::endl;
    std::cout << sum2(1, 2, 3, 4) << std::endl;


    return 0;
}