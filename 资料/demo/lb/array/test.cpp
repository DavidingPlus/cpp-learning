//test.cpp

#include <iostream>
#include <format>

#include "array.h"

void print_l(auto& l) {
    l.traverse([](auto& v) { std::cout << v << ' '; });
    std::cout << std::endl;
}

// 友元函数的实现
template <typename value_t, size_t n>
array<value_t, n>::pointer gget_a(array<value_t, n>& a) {
    return a.a; // 在类外直接访问类的私有成员
}

int main() {
    array<int, 6> l{1, 2, 3, 4, 5, 6};

    for (auto e : l)
        std::cout << e << ' ';
    std::cout << std::endl;
    
    // print_l(l);
    // std::cout << l[5] << std::endl; // 将导致异常

    // auto a = l.get_a();
    // std::cout << a[2] << std::endl;

    // auto b = (array{11, 22, 33}).get_a(); // b是一个智能指针
    // std::cout << *b << std::endl;

    // delete[] b;

    return 0;
}