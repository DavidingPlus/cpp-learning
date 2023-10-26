// testdlist.cpp
#include <format>
#include <iostream>

#include "dlist.h"

// 增加一个复杂类型
struct foo {
    int i;
    double d;

    foo(int _i = 0, double _d = 0) : i(_i), d(_d) {}

    foo(const foo& other) : i(other.i), d(other.d) {
        std::cout << "foo: copy ctor" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const foo& f) {
    return os << std::format("({},{})", f.i, f.d);
}

template <typename value_t>
void print_l(dlist<value_t>& l) {
    l.traverse([](auto& val) { std::cout << val << ' '; });
    std::cout << std::endl;
}

template <typename iterator>
void print_l(iterator first, iterator last) {
    for (auto iter = first; iter != last; ++iter)
        std::cout << *iter << ' ';
    std::cout << std::endl;
}

namespace Test {

void test1() {
    dlist<int> l{1, 2, 3, 4, 5, 6};
    print_l(l);

    // l.traverse([](int& val) { std::cout << val << ' '; });
    // std::cout << std::endl;

    dlist<char> l2{'A', 'B', 'C'};
    print_l(l2);

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

void test3() {
    // 测试复杂类型
    dlist<foo> l3;
    for (int i = 1; i <= 10; ++i) {
        // l3.push_back(foo{i, i * 1.23});
        l3.emplace_back(i, i * 1.23);
    }
    print_l(l3);
}

// 测试迭代器
void test4() {
    dlist<foo> l;
    for (int i = 1; i <= 10; ++i) {
        l.emplace_back(i, i * 1.23);
    }

    for (auto& e : l)
        std::cout << e << ' ';
    std::cout << std::endl;

    print_l(l.begin(), l.end());

    print_l(l.begin() + 3, l.end() - 2);

    print_l(l.rbegin() + 3, l.rend() - 2);
}

}  // namespace Test

int main() {
    // Test::test1();
    // Test::test2();
    // Test::test3();
    Test::test4();

    return 0;
}
