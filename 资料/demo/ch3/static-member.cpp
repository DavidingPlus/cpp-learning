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
//statci-member.cpp

#include <iostream>

class foo {
private:
    int a;
    static int b;

public:
    static int c;

    void set(int x) {
        a = x;
    }
    static void f() {
        std::cout << b << ' ' << c << std::endl;
    }
    static void g(const foo &o) {
        std::cout << o.a << std::endl;
    }
};

int foo::b = 0;
int foo::c = 1;

int main() {
    foo o;

    o.set(3);
    foo::f();
    foo::g(o);

    //++foo::b; //error
    ++foo::c;
    foo::f();
    o.f(); //OK, but not good

    return 0;
}
