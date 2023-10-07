// testarray.cpp
#include <format>
#include <iostream>

#include "array.h"

void print_l(array& l) {
    l.traverse([](auto& val) { std::cout << val << ' '; });
    std::cout << std::endl;
}

typename array::pointer get_pointer2(array& a) {
    return a.data;
}

namespace Test {

void test1() {
    array l{1, 2, 3, 4, 5, 6};
    print_l(l);
    std::cout << l.at(3) << std::endl;

    // 测试将亡对象
    auto p = (array{11, 22, 33}).get_pointer();
    std::cout << *p << std::endl;
    // delete[] p; //使用了智能指针，这里就不用手动释放了

    // 测试友元
    auto q = get_pointer2(l);
    std::cout << q[4] << std::endl;
}

void test2() {
    array l{1, 2, 3, 4, 5, 6};

    array l2;
    l2 = l;   // 拷贝赋值(拷贝构造是对的，因为调用的拷贝赋值)
    l2 = l2;  // 检测自我赋值
    print_l(l2);
}

}  // namespace Test

int main() {
    Test::test1();

    std::cout << std::endl;

    Test::test2();

    return 0;
}
