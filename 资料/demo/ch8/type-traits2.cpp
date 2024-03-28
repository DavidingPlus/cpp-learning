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
//type-traits2.cpp

#include <iostream>

void g(int) { std::cout << "g(int)" << std::endl; }
void g(char) { std::cout << "g(char)" << std::endl; }
//error handler somehow
void g(void*) { std::cout << "error" << std::endl; }

template <typename T>
struct A { using type_t = T; };

//normal version for any types except sepcialized types
template <typename T> struct type_traits { using type_t = void*; };
//partial specialization for template A only
template <typename T> struct type_traits<A<T>> { using type_t = typename A<T>::type_t; };
//specialization for int only
template <> struct type_traits<int> { using type_t = int; };
//specialization for char only
template <> struct type_traits<char> { using type_t = char; };

template <typename U>
void f(U) { typename type_traits<U>::type_t v; g(v); }

struct B {}; //doesn't have any nested types

int main() {
    f(1);
    f('A');
    f(A<int>());
    f(A<char>());
    f(B());
    f(1.0);
    return 0;
}
