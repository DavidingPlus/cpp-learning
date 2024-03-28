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
//rangebasedfor.cpp

#include <iostream>

int main() {
    int a[] = {1, 2, 3, 4, 5}; //数组是一种范围

    for (auto &&val : a) ++val;
    for (auto val : a) std::cout << val << ' ';
    std::cout << std::endl;

    for (auto val : {1.2, 2.3, 3.4, 4.5}) std::cout << val << ' ';
    std::cout << std::endl;

    auto list = {9.8, 8.7, 7.6, 6.5, 5.4}; //花括号初始化列表也是一种范围
    for (auto val : list) std::cout << val << ' ';
    std::cout << std::endl;

    //for (auto val : {1, 2.0}) ++val;//error，花括号初始化列表中的值类型不统一
    //int *p = a;
    //for (auto val : p) --val; //error，这种for不能用于指向数组元素的指针

    int (*q)[5] = &a; //q是数组指针，它与p完全不一样
    for (auto& val : *q) --val; //OK，q指向的是数组，而非数组元素

    return 0;
}
