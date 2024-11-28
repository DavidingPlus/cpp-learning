// fun-tpl-abbr.cpp
#include <iostream>

template <typename value_type>
auto add(value_type a, value_type b) {
    return a + b;
}

// 函数模板缩写，注意这仍然是一个模板！类型是自己推导的
auto add2(auto a, auto b) {
    return a + b;
}

// 如果我们要求a和b的类型相同，但是可能会出现double缩窄为int导致精度丢失的问题
auto add3(auto a, decltype(a) b) {
    return a + b;
}

// 解决方法1：重载一个实函数
// auto add(int a, double b) {
//     return a + b;
// }

// 解决方法2：特化，但是这里并不能解决问题，因为我们模板的设定是两个类型相同
// template <>
// auto add<int>(int a, double b) {
//     return a + b;
// }

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << add(3.3, 4.4) << std::endl;

    std::cout << add2(1, 2.2) << std::endl;  // 两个类型不同

    return 0;
}
