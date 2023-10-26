// typetraits.cpp

#include <format>
#include <iostream>
#include <typeinfo>

// 类模板：带有内部类型的模板
template <typename T>
struct X {
    using value_type = long;
};

// 类型的traits
// 任意的内部类型，给出type_traits为T
template <typename T>
struct type_traits {
    using value_type = T;
};

// 对X类型作偏特化
template <typename T>
struct type_traits<X<T>> {
    using value_type = typename X<T>::value_type;
};

// 函数模板：生成一个类型T内部类型的临时对象
template <typename T>
auto f() {
    return typename type_traits<T>::value_type{};  // 我们获取类型都交给中间type_traits进行处理，萃取剂对不同的情况都做了考虑，可以认为是万能的
};

// 打印f()返回值的类型名
template <typename T>
void type_name() {
    std::cout << typeid(f<T>()).name() << std::endl;
}

int main() {
    type_name<X<int>>();
    type_name<int>();

    return 0;
}
