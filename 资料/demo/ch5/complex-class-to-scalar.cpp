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
//complex-class-to-scalar.cpp

#include <iostream>
#include <format>
#include <cmath>
using namespace std;

class complex {
private:
    double real, imag;

public:
    complex(double r = 0, double i = 0) : real(r), imag(i) {}

    operator double() {
        return sqrt(real * real + imag * imag);
    }

    friend istream &operator>>(istream &is, complex &b);
    friend ostream &operator<<(ostream &os, const complex &b);
};

istream &operator>>(istream &is, complex &b) {
    return is >> b.real >> b.imag;
}

ostream &operator<<(ostream &os, const complex &b) {
    return os << format("{:.2f} + i{:.2f}\n", b.real, b.imag);
}

int main() {
    complex x{1.2, 2.3};
    double d = x;

    cout << d << endl;

    return 0;
}

