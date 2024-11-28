// complex-case.cpp
#include <cmath>  //不加.h，前面加c，表示引入C语言的库
#include <format>
#include <iostream>

class complex {
private:
    double real, imag;

public:
    complex(double r = 0, double i = 0) : real(r), imag(i) {}

    complex& operator+=(const complex& b) {
        real += b.real;
        imag += b.imag;
        return *this;
    }

    // 前缀自增
    complex& operator++() {  // 后缀自增的优先级高于前缀自增
        ++real;
        return *this;
    }

    // 后缀自增
    complex operator++(int) {  // 添加一个参数来区别前缀自增
        complex t{*this};
        ++real;
        return t;
    }

    double operator()() {
        return sqrt(real * real + imag * imag);
    }

    friend complex operator+(const complex& a, const complex& b);

    // 流输出
    friend std::ostream& operator<<(std::ostream& os, const complex& c);

    friend void print(const complex& c);
};

complex operator+(const complex& a, const complex& b) {
    return complex{a.real + b.real, a.imag + b.imag};
}

std::ostream& operator<<(std::ostream& os, const complex& c) {
    return os << std::format("{:.2f} + i{:.2f}", c.real, c.imag);
};

void print(const complex& c) {
    std::cout << c;
}

int main() {
    complex c1{1.2, 2.3}, c2{3.4, 4.5}, c3;
    c3 = c1 + c2;  // 显示调用方式  ::operator+(c1, c2)   运算符语义：运算符本来的含义，是否产生新值，是否改变原值，是否可以级联
    // print(c3);
    std::cout << c3 << std::endl
              << c3() << std::endl;

    return 0;
}

// 赋值类表达式的结果都是左值，eg：a += b（可级联）
