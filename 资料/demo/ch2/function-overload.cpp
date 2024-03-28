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
//function-overload.cpp

#include <iostream>

int f() {
    return 0;
}

int f(int i) {
    return i;
}

//char f() { return '1'; } //error，重载函数仅返回类型不同
//int f(int i = 0) { return i; } //error，缺省参数导致不能区分与无参版的区别
int f(int &i) { //OK
    return i;
}

int main() {
    [[maybe_unused]] int a = 1;

    std::cout << f() << std::endl;
    // std::cout << f(a) << std::endl; //error，无法区分调用的是f(int)还是f(int&)

    return 0;
}
