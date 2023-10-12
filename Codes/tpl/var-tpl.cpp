// var-tpl.cpp
#include <iostream>

size_t fibo_r(size_t n) {
    return n < 3 ? 1 : (fibo_r(n - 1) + fibo_r(n - 2));
}

int main() {
    size_t n = 10;
    std::cout << fibo_r(n) << ' ' << fibo_r(40) << std::endl;

    return 0;
}
