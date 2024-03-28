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
//variadic-paramter.cpp

#include <iostream>

struct A { A() { std::cout << "base-class A" << std::endl; } };
struct B { B() { std::cout << "base-class B" << std::endl; } };
struct C { C() { std::cout << "base-class C" << std::endl; } };

template <typename ...bases>
struct D : public bases... { 
    D() : bases()... 
    { std::cout << "D has " << sizeof...(bases) << " base classes." << std:: endl; } 
};

int main() {
    D<A> o1;
    D<A, C> o2;
    D<A, B, C> o3;
    return 0;
}
