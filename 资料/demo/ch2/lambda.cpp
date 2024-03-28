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
//lambda.cpp

#include <iostream>
#include <format>

int main() {
    int a = 1, b = 2;

    auto square = [](int x) { return x * x; }; //lamda的类型必须是auto
    auto add3 = [a, b](int t) { return a + b + t; }; //捕获包围块中的对象a和b
    auto mul = [](auto a, auto b) { return a * b; }; //参数类型自动推导
    auto noargs = [a, b] { return a * b; }; //lambda没有参数时，可以省略()

    std::cout << std::format("{} {} {}\n", square(add3(3)), mul(1, 2.3), noargs());

    return 0;
}
