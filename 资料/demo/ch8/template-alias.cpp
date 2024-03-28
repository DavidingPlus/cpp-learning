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
//template-alias.cpp

#include <iostream>

template <typename T>
bool lt(T a, T b) { return a < b; }

template <typename T>
bool gt(T a, T b) { return a > b; }

//alias of function template
template <typename T>
using callback = bool (T, T);

template <typename T>
class X {
private:
    T d;

public:
    X(T y) : d(y) {}
    operator T() { return d; }  //type casting
};

//alias of class template
template <typename T>
using Y = X<T>;

//alias of class
using Z = X<double>;

int main()
{
    int a{1}, b{2};
    double c{4.0}, d{-1.0};
    auto bool2literal = [](auto a, auto b, callback<decltype(a)> f) 
    { std::cout << (f(a, b) ? "true" : "false") << std::endl; }; //泛型lambda

    bool2literal(a, b, lt);
    bool2literal(c, d, gt);

    bool2literal(Y<int>(3), Y<int>(2), lt);
    bool2literal(Z(3), Z(2), gt);

    return 0;
}
