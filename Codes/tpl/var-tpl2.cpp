// var-tpl.cpp
#include <iostream>

size_t fibo_r(size_t n) {
    return n < 3 ? 1 : (fibo_r(n - 1) + fibo_r(n - 2));
}

// 定义一个变量模板，他没有类型参数，只给了一个变量的参数
// 告诉编译器这个是一个编译期常量，不需要在运行的时候计算，在编译器的时候就可以计算出来，提高效率
// 模板元编程
template <size_t N>
constexpr size_t fibo_v = fibo_v<N - 1> + fibo_v<N - 2>;

// 特化
template <>
constexpr size_t fibo_v<1> = 1;

template <>
constexpr size_t fibo_v<2> = 1;

int main() {
    size_t n = 10;

    // 这个变量模板是一个编译期常量，在编译的时候就会被计算出来，提高了效率
    // 这里是显式实例化，就是必须给出模板参数
    std::cout << fibo_r(n) << ' ' << fibo_v<40uz> << std::endl;

    return 0;
}
