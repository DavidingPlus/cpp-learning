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
//template-recursion-var.cpp

#include <iostream>

//递归的变量模板。将耗费更多的编译时间，但节省了运行时间。
template <long N>
auto fact = N * fact<N-1>;

//特化的模板，用于指示递归的终点
template <>
auto fact<1> = 1;

int main() {
    std::cout << fact<10>; //实际上是输出一个常量

    return 0;
}

