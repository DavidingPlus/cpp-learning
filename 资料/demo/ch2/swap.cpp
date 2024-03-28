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
//swap.cpp

#include <iostream>
#include <format>

void swap_byval(int a, int b) {
    int t = a;
    a = b;
    b = t;
}

void swap_byptr(int *pa, int *pb) {
    int t = *pa;
    *pa = *pb;
    *pb = t;
}

void swap_byref(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    int i = 11, j = 99;

    std::cout << std::format("Swap By Value:\ni = {}, j = {}\n", i, j);
    swap_byval(i, j);
    std::cout << std::format("i = {}, j = {}\n", i, j);

    i = 10; j = 20;
    std::cout << std::format("Swap By Pointer:\ni = {}, j = {}\n", i, j);
    swap_byptr(&i, &j);
    std::cout << std::format("i = {}, j = {}\n", i, j);

    i = 10; j = 20;
    std::cout << std::format("Swap By Reference:\ni = {}, j = {}\n", i, j);
    swap_byref(i, j);
    std::cout << std::format("i = {}, j = {}\n", i, j);

    return 0;
}
