// var-tpl.cpp
#include <iostream>

// consteval告诉编译器这是一个立即函数，这种情况下我们必须传入一个常量，这样保证在编译时就能被计算
// 为了使用这一点，在编译的时候需要使用c++23，至少c++20
// 那么怎么解决变量的问题呢？用重载解决
// TODO
consteval size_t fibo_r(size_t n) {
    return n < 3 ? 1 : (fibo_r(n - 1) + fibo_r(n - 2));
}

int main() {
    size_t n = 10;  // 说明n是一个编译期常量
    // n是变量，40是常量
    // 那么40对应的函数的值是固定的，我们其实可以在编译的时候就让他计算出来，而不是在运行时候跑出来
    // 怎么办？告诉编译器这是一个立即函数，编译遇到的时候就立即执行
    std::cout << fibo_r(n) << ' ' << fibo_r(40) << std::endl;

    return 0;
}
