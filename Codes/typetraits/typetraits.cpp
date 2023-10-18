//typetraits.cpp

#include <iostream>
#include <format>
#include <typeinfo>

// 类模板：带有内部类型的模板
template <typename T>
struct X {
    using value_type = long;
};

// 函数模板：生成一个类型T内部类型的临时对象
template <typename T>
auto f() {
    return typename T::value_type{};
};

// 打印f()返回值的类型名
template <typename T>
void type_name() {
    std::cout << typeid(f<T>()).name() << std::endl;
}

int main() {
    type_name<X<int>>();
    
    return 0;
}