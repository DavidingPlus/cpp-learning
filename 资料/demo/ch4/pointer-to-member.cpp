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
//pointer-to-member.cpp

#include <iostream>

class Y {
private:
    int a;

public:
    int b;

    Y(int i, int j) : a(i), b(j) {}
    int f() { return a; }
    int g() { return b; }
};

int main() {
    Y o{1, 2};

    int Y::*ptr = &Y::b;
    ++(o.*ptr);
    std::cout << o.b << std::endl;

    using YFPTR = int (Y::*)(); //YFPTR是指向Y的成员函数的指针类型
    YFPTR fptr = &Y::f;
    std::cout << (o.*fptr)() << std::endl;
    fptr = &Y::g;
    std::cout << (o.*fptr)() << std::endl;

    return 0;
}
