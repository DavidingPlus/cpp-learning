//var-tpl.cpp

#include <iostream>

size_t fibo_r(size_t n) {
    return n < 3 ? 1 : (fibo_r(n - 1) + fibo_r(n - 2));
}

template <size_t N>
constexpr size_t fibo_v = fibo_v<N-1> + fibo_v<N-2>;

template <>
constexpr size_t fibo_v<1> = 1;

template <>
constexpr size_t fibo_v<2> = 1;

int main() {
    size_t n = 10;
    std::cout << fibo_r(n) << ' ' << fibo_v<40uz> << std::endl;

    return 0;
}