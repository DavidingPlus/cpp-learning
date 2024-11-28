// abs.cpp
#include <iostream>

// 函数模板如果没有实例化的话，就不会被编译
// 函数模板是隐式实例化
template <typename value_type, value_type zero = value_type(0)>
auto abs(value_type val) {
    return val < zero ? -val : val;
}

// 为指针类型写一个特化版本，而且是偏特化
// 函数模板的偏特化不被允许，我们一般对类做偏特化，我们只是看一下偏特化的写法
template <typename value_type>
auto abs<value_type*>(value_type* ptr) {  // error
    return ptr;
}

// struct X {};

int main() {
    // 在编译的时候编译器会自动的对对应的类型生成对应类型的模板函数
    std::cout << abs<decltype(-2), 0uz>(-2) << std::endl;
    std::cout << abs(-2.2) << std::endl;

    // std::cout << abs(X()) << std::endl;  // error

    // int a = 1, *p = &a;
    // std::cout << abs(p) << std::endl;  // 编译器错误

    return 0;
}
