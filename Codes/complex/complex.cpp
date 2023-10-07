#include <format>
#include <iostream>

class complex {
public:
    complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 重载+号运算符，为了访问私有成员，设置成为友元
    friend complex operator+(const complex &a, const complex &b);

    // 对友元的理解：其实就是把一个普通的函数放到类的内部，只不过这个普通的函数可以访问类内部的私有成员，由于需要访问类内部的私有成员，所以参数里面需要给一个类的对象!!
    friend void print(const complex &c);

private:
    double real, imag;
};

void print(const complex &c) {
    std::cout << std::format("{:.2f} + i{:.2f}\n", c.real, c.imag);
}

complex operator+(const complex &a, const complex &b) {
    return complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    complex c1{1.2, 2.3}, c2{3.4, 4.5}, c3;
    c3 = c1 + c2;  // 显式调用 ::operator+(c1,c2)，注意作用域是全局
    print(c3);

    return 0;
}
