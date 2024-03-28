/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */


//bzj^_^
//complex-class-to-class.cpp

#include <iostream>
#include <format>
#include <cmath>

using namespace std;

class complexa; //forwarding

class complex {
private:
    double real, imag;

public:
    complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    operator class complexa(); //仅声明，实现放在complexa类定义的后面
    friend ostream &operator<<(ostream &os, const complex &b);
};

class complexa {
private:
    double r, a;

public:
    complexa(double rr = 0.0, double aa = 0.0) : r(rr), a(aa) {}

    operator complex() {
        return complex{r * cos(a), r * sin(a)};
    }

    friend ostream &operator<<(ostream &os, const complexa &b);
};

complex::operator complexa() {
    return complexa{sqrt(real * real + imag * imag), atan2(imag, real)};
}

ostream &operator<<(ostream &os, const complex &b) {
    return os << format("{:.2f} + i{:.2f}\n", b.real, b.imag);
}

ostream &operator<<(ostream &os, const complexa &b) {
    return os << format("{:.2f} * e^i{:.2f}\n", b.r, b.a);
}

int main() {
    complex a{3.0, 4.0};
    complexa b;
    b = a; //等价于b = complexa(a)
    cout << a << b;
    complex c;
    c = b; //等价于c = complex(b)
    cout << c;
    return 0;
}
