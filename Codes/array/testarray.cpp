// testarray.cpp
#include <format>
#include <iostream>

#include "array.h"

template <typename value_t, size_t n>
void print_l(array<value_t, n>& l) {
    l.traverse([](auto& val) { std::cout << val << ' '; });
    std::cout << std::endl;
}

template <typename value_t, size_t n>
typename array<value_t, n>::pointer get_pointer2(array<value_t, n>& a) {
    return a.data;
}

namespace Test {

void test1() {
    array<int, 6> l{1, 2, 3, 4, 5, 6};
    print_l(l);
    std::cout << l.at(3) << std::endl;

    // 测试将亡对象
    // auto p = (array<int, 3>{11, 22, 33}).get_pointer();
    // std::cout << *p << std::endl;
    // delete[] p; //使用了智能指针，这里就不用手动释放了

    // 测试友元
    auto q = get_pointer2(l);
    std::cout << q[4] << std::endl;
}

void test2() {
    array<int, 6> l{1, 2, 3, 4, 5, 6};

    array<int, 6> l2;
    l2 = l;   // 拷贝赋值(拷贝构造是对的，因为调用的拷贝赋值)
    l2 = l2;  // 检测自我赋值
    print_l(l2);
}

// 测试迭代器
void test3() {
    array<int, 6> l{1, 2, 3, 4, 5, 6};
    for (auto& e : l)  // for_each要求如果不是原生容器(例如原生数组，初始化列表)，必须具有迭代器，因为他本质是通过迭代器遍历的
        std::cout << e << ' ';
    std::cout << std::endl;
}

}  // namespace Test

int main() {
    Test::test1();

    std::cout << std::endl;

    Test::test2();

    std::cout << std::endl;

    Test::test3();

    return 0;
}
