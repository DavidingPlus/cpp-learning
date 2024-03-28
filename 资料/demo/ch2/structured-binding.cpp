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
//structured-binding.cpp

#include <iostream>
#include <format>

struct X {
    int a;
    double b;
};

X f() {
    return {1, 2.3};
}

int main() {
    auto [a, b] = f();
    std::cout << std::format("{} {}\n", a, b);

    double arr[] = {1.2, 3.4, 5.6};
    auto [c, d, e] = arr;
    std::cout << std::format("{} {} {} {}\n", c, d, e, arr[2]);

    return 0;
}
