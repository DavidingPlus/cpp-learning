// testdlist.cpp
#include <format>
#include <iostream>

#include "dlist.h"

template <typename value_t>
void print_l(dlist<value_t>& l) {
    l.traverse([](auto& val) { std::cout << val << ' '; });
    std::cout << std::endl;
}

namespace Test {

void test1() {
    dlist<int> l{1, 2, 3, 4, 5, 6};
    print_l(l);

    l.traverse([](auto& val) { ++val; });
    l.insert(6, 7);
    print_l(l);

    l.insert(10, 9);  // 测试抛出异常
}

void test2() {
    dlist<int> l{1, 2, 3, 4, 5, 6};

    dlist<int> l2;
    l2 = l;   // 拷贝赋值(拷贝构造是对的，因为调用的拷贝赋值)
    l2 = l2;  // 检测自我赋值
    print_l(l2);
}

}  // namespace Test

int main() {
    Test::test1();
    // Test::test2();

    return 0;
}
