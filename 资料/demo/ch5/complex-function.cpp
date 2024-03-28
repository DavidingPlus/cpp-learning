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
//complex-function.cpp

#include <iostream>
#include <format>

class complex {
private:
    double real, imag;

public:
    complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double &operator()(char part) {
        return part == 'r' ? real : imag;
    }
};

int main() {
    complex c{1.2, 2.3};

    ++c('r'); c('i')--;
    std::cout << std::format("real part: {:.2f}, imaginary part: {:.2f}\n", c('r'), c('i'));

    return 0;
}
