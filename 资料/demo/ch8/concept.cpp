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
//concept.cpp

// #include <iostream>
// #include <string>
// #include <concepts>

#include <iostream>
#include <string>
#include <concepts>

template <typename T>
inline constexpr bool not_boolean = true; //判断是否是bool类型的模板变量

template <>
inline constexpr bool not_boolean<bool> = false; //特化的模板变量

//概念：两个操作数是可相加的，并且不是bool类型
template <typename T>
concept addable = requires(T a, T b) { a + b; } and not_boolean<T>;

template <addable T>
auto add(const T& a, const T& b) {
    return a + b;
}

template <typename ...types>
void println(types&& ...args) {
    (std::cout << ... << args);
    std::cout << std::endl;
}

int main() {
    println(add(1, 2));
    println(add(4.5, 7.8));

    // println(add(true, false));  //error

    // int a, *p = &a, b, *q = &b;
    // println(add(p, q)); //error

    // struct X {};
    // println(add(X(), X())); //error

    std::string a{"hello"}, b{", world"};
    println(add(a, b));

    return 0;
}