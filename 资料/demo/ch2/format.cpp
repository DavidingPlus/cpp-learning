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
//format.cpp

#include <iostream>
#include <format>

int main() {
    int a = 1, b = 3;
    double c = 3.1415926;
    const char *s1 = "one", *s2 = "two";

    //占位符格式：{[序号][:[精度]]}
    std::cout << std::format("a={1}, b={0}, c={2:.5f}\n", b, a, c);
    std::cout << std::format("{} {}\n", s1, s2);
    
    return 0;
}
