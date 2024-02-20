#include <functional>
#include <iostream>

// std::function绑定带捕获的lambda和不带捕获的lambda
void test1() {
    // 不带捕获的lambda
    std::function<int(int, int)> f = [](int a, int b) { return a + b; };

    std::cout << f(1, 2) << '\n'
              << '\n';

    // 带捕获的lambda
    int num = 1;
    std::cout << "num: " << num << '\n';

    std::function<int(int, int)> f2 = [&num](int a, int b) {
        num = 2;
        return a + b;
    };

    std::cout << f2(1, 2) << '\n';
    std::cout << "num: " << num << '\n';
}

int add(int a, int b) { return a + b; }

// std::function绑定普通函数
void test2() {
    std::function<int(int, int)> f = add;

    std::cout << f(1, 2) << '\n';
}

// std::function绑定成员函数
class Math {
public:
    int add2(int a, int b) { return a + b; }
};

void test3() {
    Math m;

    // 这个写法比较特殊
    std::function<int(int, int)> f = std::bind(&Math::add2, &m, std::placeholders::_1, std::placeholders::_2);
    std::cout << f(1, 2) << '\n';
}

int main() {
    test1();
    std::cout << "-------------------------------" << '\n';
    test2();
    std::cout << "-------------------------------" << '\n';
    test3();

    return 0;
}
