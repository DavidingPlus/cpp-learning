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
//lvalue-ref.cpp

#include <iostream>
#include <format>

int main() {
    int a = 0;
    int &ra = a;

    std::cout << std::format("a={}, ra={}\n", a, ra);

    ++ra;
    std::cout << std::format("a={}, ra={}\n", a, ra);

    int b = 3;
    ra = b; //这不是引用绑定，而是赋值
    std::cout << std::format("a={}, b={}, ra={}\n", a, b, ra);

    return 0;
}
