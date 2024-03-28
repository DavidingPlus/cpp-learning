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
//typedef.cpp

#include <iostream>

void f() {
    std::cout << 'A';
}
//void g(void (*p)()) { (*p)(); }
//void (*(h()))() { return f; } //terrible!

//typedef void (*FUN_PTR)(); //FUN_PTR是指向函数的指针类型的名字，不是对象名
using FUN = void ();
using FUN_PTR = void (*)();

void g(FUN p) {
    (*p)();
}

FUN_PTR h() {
    return f;
}

int main() {
    g(f);
    h()();

    return 0;
}
