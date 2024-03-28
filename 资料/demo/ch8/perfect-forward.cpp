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
//perfect-forward.cpp

#include <iostream>

void f(int&) { std::cout << "f(int&)" << std::endl; }
void f(int&&) { std::cout << "f(int&&)" << std::endl; }

template <typename T>
void wrapper1(T a) { f(a); }

template <typename T>
void wrapper2(T&& a) { f(std::forward<T>(a)); }

int main() {
    int x = 0;
    int&& rrx = std::move(x);

    wrapper1(x); //parameter is an lvalue
    wrapper1(1); //parameter is an rvalue
    wrapper1(rrx); //parameter is an lvalue!

    wrapper2(x); //parameter is an lvalue
    wrapper2(1); //parameter is an rvalue
    wrapper2(rrx); //parameter is an lvalue!

    return 0;
}
